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
#include "../include/test_car.h"
#include "../include/Model.h"
#include "../include/Score.h"
#include "../include/Map.h"
#include "../include/Crash.h"
#include "../include/traffic_light.h"
#include "../include/CarModel.h"


#define BRIDGE_SPEED 5
#define SPEED_UP 0.5
#define LEFT_ARROW 37
#define RIGHT_ARROW 39
#define INIT_SPEED 30
#define MAX_SPEED 50

using namespace std;


double z = 0;

float zoom = 150.0f;

int dt = 1;

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
Bridge bridge(BRIDGE_SPEED);

Model* car;
//Vehicle object
TestCar test_car(1, 8, 0.3, 0.4, 1);
CarModel* car_model1;
CarModel* car_model2;

bool reset = false;


void Render()
{
	//CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
						   // and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f ,300.0f,380.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);


	glPushMatrix();
	map.Render();
	light->Render(color);

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
	//test_car.Render(-L/2,-R-D,R,D,L);
	// test_car.Render(L,-R-D,R,D,L);
	if (reset) {
		glPushMatrix();
		glTranslatef(0,0,-100);
		glScalef(12,12,12);
		glRotatef(0,1,0,0);
		crash.Render();
		glPopMatrix();
		glPopMatrix();

		car_model1->Reset(INIT_SPEED);
		car_model2->Reset(INIT_SPEED);

		reset = false;
	}

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
	if (car_model1->ReachedRange(-L + 130, -L/2 + 130)) {
		if (bridge.Moving()) {
			reset = true;
		}
	}
	if (car_model2->ReachedRange(-L + 130, -L/2 + 130)) {
		if (bridge.Moving()) {
			car_model2->Stop();
		}
		else {
			car_model2->SetSpeed(INIT_SPEED);
		}
	}
	bridge.Move(dt);
	car_model1->Move(turns,2*R+D,dt);
	car_model2->Move(turns,2*R+D/4,dt);
	glutPostRedisplay();
}



void Keyboard(int key,int x,int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
			car_model1->SpeedDown(SPEED_UP);
			break;
		case GLUT_KEY_RIGHT:
			car_model1->SpeedUp(SPEED_UP);
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
	car_model1 = new CarModel(INIT_SPEED, MAX_SPEED, car, -L/2 - 120,-R-D, 40);
	car_model2 = new CarModel(INIT_SPEED, MAX_SPEED, car, -L/2 - 120,-R-D, -40);
	//Parameter handling
	glShadeModel (GL_SMOOTH);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
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

}


