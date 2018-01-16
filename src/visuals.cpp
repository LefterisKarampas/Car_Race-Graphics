#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "GL/freeglut.h"
#include "../include/visuals.h"
#include "../include/custom_vertexes.h"
#include "../include/bridge.h"
#include "../include/vehicle.h"
#include "../include/Model.h"
#include "../include/Score.h"
#include "../include/Map.h"
#include "../include/Crash.h"
#include "../include/traffic_light.h"
#include "../include/CarModel.h"
#include "../include/functions.h"

using namespace std;

float dt = 1;
float vA = 20;
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
bool reset = false;
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
	ShowInformation(car_model1->GetSpeed());

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


void Setup()  // TOUCH IT !! 
{ 
	score.LoadScore();
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