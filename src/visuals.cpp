#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "GL/freeglut.h"   // - An interface and windows management library
#include "../include/visuals.h"   // Header file for our OpenGL functions
#include "../include/custom_vertexes.h"
#include "../include/bridge.h"
#include "../include/vehicle.h"
#include "../include/Model.h"
#include "../include/Score.h"
#include "../include/Map.h"
#include "../include/Crash.h"
#include "../include/traffic_light.h"
#include "../include/CarModel.h"

#define COUNTDOWN 10
#define BRIDGE_SPEED 1.3
#define LEFT_ARROW 37
#define RIGHT_ARROW 39
#define ROUNDS 3
using namespace std;


double z = 0;

float zoom = 150.0f;

	
float dt = 1;
float vA = 18;
float vOr = 50;
float vMax = 60;
float tEid = 10;
float a = 3;
float d = 7;
float dtMax = 3;

extern char * light_input;
extern char *car_input;

//Grid parameters
double R = 100.0f;	//radius
double D = 100.0f;	
double L = 150.0f;	//length

//turns coordinates
float* turns;
int next_turn = 0;

Map map(R,D,L);
Score score;
Crash crash;
traffic_light *light;


Model* car;
//Vehicle object
CarModel* car_model1;
CarModel* car_model2;
Bridge *bridge;
bool score_flag = false;
int count = COUNTDOWN;
bool reset = true;
bool crash_flag = false;
int start = 0;
int v = 0;
float eye_y = 300.0f; 
float eye_z = 380.0f;
float board_rotate = 0;
int dif_level = 0;
int players = 1;
int print_flag = 0;

void Render()
{
	//CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
						   // and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f ,eye_y,eye_z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);


	glPushMatrix();

	glPushMatrix();
	if(v){
		glTranslatef(10,0,-15);
		glScalef(1.35,1.35,1.35);
	}
	map.Render();
	glPopMatrix();

	
	// Draw bridge
	glPushMatrix();
	if(v){
		glTranslatef(10,0,-15);
		glScalef(1.35,1.35,1.35);
	}
	bridge->Render(R,D,L);
	light->Render(bridge->Get_Color());
	glPopMatrix();
	float placementOffset = 80 - L/2;

	turns[0] = L + placementOffset + 2*L;
	turns[1] = -L + placementOffset + L;

	glPushMatrix();
	if(v){
		glTranslatef(0,0,220);
	}
	car_model1->Render(R,D,L);
	car_model2->Render(R,D,L);
	glPopMatrix();
	// Draw vehicle
	if (reset || crash_flag) {
		if(crash_flag){
			if(count == COUNTDOWN){
				score.away();
			}
			glPushMatrix();
			glTranslatef(0,0,-100);
			glScalef(12,12,12);
			glRotatef(0,1,0,0);
			crash.Render(board_rotate);
			glPopMatrix();
		}

		car_model1->Reset(vA);
		car_model2->Reset(vA);
		bridge->Reset();

		if(reset){
			glPushMatrix();
			char str[7];
			if(dif_level == EASY){
				strcpy(str,"EASY");
			}
			else if(dif_level == MEDIUM){
				strcpy(str,"MEDIUM");
			}
			else if(dif_level == HARD){
				strcpy(str,"HARD");
			}
			glColor3f(0.7,0.8,0.0);
			glTranslatef(-600,-1100, -1000);
			glScalef(3,3,3);
			glRotatef(-90,1,0,0);
			//glRotatef(, GLfloat x, GLfloat y, GLfloat z)
			for (int i=0;i<strlen(str);i++){
			  glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
			}
			glPopMatrix();
			if(!score_flag && count == COUNTDOWN){
				score.Reset();
			}
			score_flag = false;
		}
		if(count == 0){
			reset = false;
			crash_flag = false;
		}
		else if(count > 0){
			count--;
		}
	}
	glPushMatrix();
	if(v){
		glScalef(1.5,1.5,1.5);
	}
	score.Render(board_rotate);
	glPopMatrix();
	print_velocity(car_model1->GetSpeed());

	glPopMatrix();

	glutSwapBuffers(); // All drawing commands applied to the 
	// hidden buffer, so now, bring forward
  // the hidden buffer and hide the visible one
}

//-----------------------------------------------------------

void Resize(int w, int h)
{ 
  // define the visible area of the window ( in pixels )
  if (h==0) h=1;
  glViewport(0,0,w,h); 

  // Setup viewing volume

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
  //glOrtho (-50.0f, 50.0f, -50.0f, 50.0f,-500.0f,500.0f);
  gluPerspective(60.0, (float)w/(float)h, 1.0, 0.0);
}



void Idle()
{
	if(start){

		if (car_model1->ReachedRange(-L +3*L/2, -L/2 + 3*L/2)) {
			if (bridge->Moving()) {
				crash_flag = true;
				count = COUNTDOWN;
			}
		}
		if (car_model2->ReachedRange(-L + 3*L/2, -L/2 + 3*L/2)) {
			if(players == PLAYER2){
				if (bridge->Moving()) {
					crash_flag = true;
					count = COUNTDOWN;
				}
			}
			else{
				if (bridge->Closing()) {
					car_model2->Stop();
				}
				else {
					car_model2->SetSpeed(vA);
				}
			}
		}
		bridge->Move(dt);
		bool crash1 = car_model1->Move(turns,2*R+D,dt);
		bool crash2 = car_model2->Move(turns,2*R+D/4,dt);

		if(car_model1->GetRounds() == ROUNDS){
			score.home();
			reset = true;
			score_flag = true;
			count = COUNTDOWN;
		}
		else if(car_model2->GetRounds() == ROUNDS){
			score.away();
			reset = true;
			score_flag = true;
			count = COUNTDOWN;
		}
		if (crash1 || (crash2 && players == PLAYER2)) {
			crash_flag = true;
			count = COUNTDOWN;
		}
	}

	glutPostRedisplay();
}



void Keyboard(int key,int x,int y)
{	
	if(start){
		switch(key)
		{
			case GLUT_KEY_LEFT:
				car_model1->SpeedDown(d);
				break;
			case GLUT_KEY_RIGHT:
				car_model1->SpeedUp(a);
				break;
			case GLUT_KEY_UP:
				if (dt >= 2.0f) {
					dt += 0.1f;
				}
				else {
					dt += 0.2f;	
				}
				if (dt > dtMax) {
					dt = dtMax;
				}
				break;
			case GLUT_KEY_DOWN:
				if (dt <= 2.0f) {
					dt -= 0.1f;
				}
				else {
					dt -= 0.2f;	
				}
				if (dt < 1) {
					dt = 1;
				}
				break;
			default: 
				return;
		}
	}
	glutPostRedisplay();

}

void Mouse(int button,int state,int x,int y)
{
	//WHEELUP for zoom out
	if (button == 3){
		zoom += 20.0f;
	}
	//WHHELDOWN for zoom in
	else if(button == 4){
		zoom -=20.0f;
	}
   glutPostRedisplay();
}


void Setup()  // TOUCH IT !! 
{ 
	turns = (float*) malloc(2*sizeof(float)); // remember to free this
	light = new traffic_light(light_input,R,D);
	car = new Model(car_input);
	car_model1 = new CarModel(vA, vMax, vOr, car, -L/2 - 120,-R-D, 40);
	car_model2 = new CarModel(vA, vMax, vOr, car, -L/2 - 120,-R-D, -40);
	bridge = new Bridge(BRIDGE_SPEED, tEid);
	//Parameter handling
	glShadeModel (GL_SMOOTH);
	
	// glEnable(GL_DEPTH_TEST);
	// glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);
    
	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	// glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

}

void SelectLevel(int choice)
{
	switch (choice) {
		case EASY : 
			d = 7; 
			tEid = 13;
			vOr = 50;
			car_model1->SetvOr(vOr);
			car_model2->SetvOr(vOr);
			bridge->SetTEid(tEid);
			reset = true;
			count = COUNTDOWN;
			start = 0;
			dif_level = choice;
			break;
		case MEDIUM : 
			d = 4; 
			tEid = 10;
			vOr = 40;
			car_model1->SetvOr(vOr);
			car_model2->SetvOr(vOr);
			bridge->SetTEid(tEid);
			reset = true;
			count = COUNTDOWN;
			start = 0;
			dif_level = choice;
			break;
		case HARD :
			d = a;
			tEid = 7;
			vOr = 30;
			car_model1->SetvOr(vOr);
			car_model2->SetvOr(vOr);
			bridge->SetTEid(tEid);
			reset = true;
			count = COUNTDOWN;
			start = 0;
			dif_level = choice;
			break;
	}
}


void SelectPlayers(int choice)
{
	switch (choice) {
		case PLAYER1 : 
			players = PLAYER1;
			reset = true;
			count = COUNTDOWN;
			start = 0;
			break;
		case PLAYER2 : 
			players = PLAYER2;
			reset = true;
			count = COUNTDOWN;
			start = 0;
			break;
	}
}



void MyKeyboardFunc(unsigned char Key, int x, int y){
	switch(Key){
		case 's':{
			start = (start +1) % 2;
			reset = false;
			count = 0;
			break;
		}
		case 32:{	//SPACEBAR
			reset = true;
			count = COUNTDOWN;
			start = 0;
			break;
		}
		//Change Camera
		case 'v':{
			v = (v+1) % 2;
			if(v == 0){
				eye_y = 300.0f;
				eye_z = 380.0f;
				board_rotate = 0;
			}
			else{
				eye_y = 1000.0f;
				eye_z = 100.0f;
				board_rotate = -55;
			}
			break;
		}
		case 'e':{
			dif_level = (dif_level +1) % 3;
			SelectLevel(dif_level);
			break;
		}
		case 'a':{
			if((players == PLAYER2) && start){
				car_model2->SpeedDown(d);
			}
			break;
		}
		case 'd':{
			if((players == PLAYER2) && start){
				car_model2->SpeedUp(a);
			}
			break;
		}
		case 'p':{
			if(players == PLAYER1){
				SelectPlayers(PLAYER2);
			}
			else{
				SelectPlayers(PLAYER1);
			}
			break;
		}
		case 'x':{
			print_flag = (print_flag +1) % 2;
		}
	}
	glutPostRedisplay();
}

void print_velocity(float current){

	char str[128];
	glPushMatrix();
	glTranslatef(0,-80,-400);
	if(print_flag){
		sprintf(str,"Time elapsed: %.2lf",car_model1->GetTime()/10.0);
	}
	else{
		sprintf(str,"Current Velocity: %.2lf",current);
	}
	if(v){
		glScalef(1.5,1.5,1.5);
	}
	else{
		glScalef(1.2,1.2,1.2);
	}
	glRotatef(board_rotate,1,0,0);

	glPushMatrix();
	glTranslatef(-4*L,0,-0);
	glScalef(4.5,4.5,4.5);
	glRotatef(-20,1,0,0);
	//glRotatef(-20,0,1,0);
	glColor3f(0.5,1.0,0.5);
	glTranslatef(30,28.0,0.0);
	GLfloat size = 0.05f;
	glScalef(size,size,size);
	for (int i=0;i<strlen(str);i++){
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
	}
	glPopMatrix();


	if(print_flag){
		sprintf(str,"dt: %.1lf",dt);
	}
	else{
		sprintf(str,"Vop: %.2lf",vOr);
	}
	glPushMatrix();
	glTranslatef(-4*L,-L/2,0);
	glScalef(4.5,4.5,4.5);
	glRotatef(-20,1,0,0);
	//glRotatef(-20,0,1,0);
	glColor3f(1.0,0.0,0.0);
	glTranslatef(30,28.0,0.0);
	glScalef(size,size,size);
	for (int i=0;i<strlen(str);i++){
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
	}
	glPopMatrix();


	glPopMatrix();
}