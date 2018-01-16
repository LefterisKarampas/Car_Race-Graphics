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


#define BRIDGE_SPEED 2
#define LEFT_ARROW 37
#define RIGHT_ARROW 39

using namespace std;


double z = 0;

float zoom = 150.0f;

float dt = 1;
float vA = 20;
float vOr = 40;
float vMax = 80;
float tEid = 5;
float a = 3;
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

char color = 'g';
//Bridge object
Bridge bridge(BRIDGE_SPEED, tEid);

Model* car;
//Vehicle object
CarModel* car_model1;
CarModel* car_model2;

bool reset = false;
bool crash_flag = false;
int start = 0;
int v = 0;
float eye_y = 300.0f; 
float eye_z = 380.0f;

void Render()
{
	//CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
						   // and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f ,eye_y,eye_z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);


	glPushMatrix();
	map.Render();
	// light->Render(color);

	glPushMatrix();
	//glTranslatef(-20,-20,0);
	glScalef(0.2,0.2,0.2);
	glRotatef(-90,1.0,0.0,0.0);
	glRotatef(180,0.0,0.0,1.0);
	glColor3f(0.1f, 0.3f, 0.3f);
	glPopMatrix();
	
	// Draw bridge
	bridge.Render(R,D,L);
	light->Render(bridge.Get_Color());

	float placementOffset = 80 - L/2;

	turns[0] = L + placementOffset + 2*L;
	turns[1] = -L + placementOffset + L;


	car_model1->Render(R,D,L);
	car_model2->Render(R,D,L);
	// Draw vehicle
	if (reset || crash_flag) {
		glPushMatrix();
		glTranslatef(0,0,-100);
		glScalef(12,12,12);
		glRotatef(0,1,0,0);
		if(crash_flag)
			crash.Render();
		glPopMatrix();

		car_model1->Reset(vA);
		car_model2->Reset(vA);

		if(reset){
			score.Reset();
		}

		reset = false;
		crash_flag = false;
	}
	score.Render();

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

		if (car_model1->ReachedRange(-L + 3*L/2, -L/2 + 3*L/2)) {
			if (bridge.Moving()) {
				crash_flag = true;
			}
		}
		if (car_model2->ReachedRange(-L + 3*L/2, -L/2 + 3*L/2)) {
			if (bridge.Moving()) {
				car_model2->Stop();
			}
			else {
				car_model2->SetSpeed(vA);
			}
		}
		bridge.Move(dt);
		bool crash1 = car_model1->Move(turns,2*R+D,dt);
		bool crash2 = car_model2->Move(turns,2*R+D/4,dt);

		if (crash1) {
			crash_flag = true;
		}
	}

	glutPostRedisplay();
}



void Keyboard(int key,int x,int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
			car_model1->SpeedDown(a);
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
	//Parameter handling
	glShadeModel (GL_SMOOTH);
	
	// glEnable(GL_DEPTH_TEST);
	// glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);
    
	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	// glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

}

void MenuSelect(int choice)
{
	switch (choice) {
		default:
			break;
	}
	glutPostRedisplay();
}


void MyKeyboardFunc(unsigned char Key, int x, int y){
	switch(Key){
		case 's':{
			start = (start +1) % 2;
			break;
		}
		case 32:{	//SPACEBAR
			reset = true;
			start = 0;
			break;
		}
		//Change Camera
		case 'v':{
			v = (v+1) % 2;
			if(v == 0){
				eye_y = 300.0f;
				eye_z = 380.0f;
			}
			else{
				;
			}
		}
	}
	glutPostRedisplay();
}

void print_velocity(float current){
	char str[128];
	sprintf(str,"Current Velocity: %.2lf",current);
	glPushMatrix();
	glTranslatef(0,-80,-450);
	glScalef(1.2,1.2,1.2);
	glPushMatrix();
	glTranslatef(-4*L,0,-0);
	glScalef(4.5,4.5,4.5);
	glRotatef(-20,1,0,0);
	//glRotatef(-20,0,1,0);
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(20,0);
	glVertex2f(20,40);
	glVertex2f(120,40);
	glVertex2f(120,0);
	glEnd();
	glColor3f(0.5,1.0,0.5);
	glTranslatef(30,28.0,0.0);
	GLfloat size = 0.05f;
	glScalef(size,size,size);
	for (int i=0;i<strlen(str);i++){
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
	}
	glPopMatrix();

	sprintf(str,"Vop: %.2lf",vOr);
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