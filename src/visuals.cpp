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

#define BRIDGE_SPEED 0.01
#define SPEED_UP 0.5
#define LEFT_ARROW 37
#define RIGHT_ARROW 39

using namespace std;


double z = 0;

float zoom = 150.0f;

int dt = 1;

//Grid parameters
double R = 100.0f;	//radius
double D = 100.0f;	
double L = 150.0f;	//length

//turns coordinates
float turns[4][3];
int next_turn = 0;
bool turning = false;

//Bridge object
Bridge bridge(BRIDGE_SPEED);

//Vehicle object
TestCar test_car(1, 8, 0.3, 0.4, 1);


void keimeno(const char *str,float size)
{

	glPushMatrix();
	glScalef(size,size,size);

	for (int i=0;i<strlen(str);i++)
	  glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	glPopMatrix();
}

void Render()
{
	//CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
						   // and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f,zoom, 0.0f, 0.0f, -5.0f, 0.0f, 1.0f, 0.0f);


	glPushMatrix();
	glTranslatef(0.0,0.0,-500.0);
	glColor3f(1.0, 0.9, 0.0);

	//Create down road
	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	glVertex2f(-L,-R-D);
	glVertex2f(L,-R-D);
	glVertex2f(-L,-R);
	glVertex2f(L,-R);
	glEnd();
	glPopMatrix();
	turns[0][0] = L;
	turns[0][1] = -R-D;
	turns[0][2] = -R;

	int num_segments = 5000;
	//Draw right half circle
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	TwoSemiCirclesVertexes(L,0,R,R+D,num_segments,true);
	glEnd();
	glPopMatrix();
	turns[1][0] = L;
	turns[1][1] = R;
	turns[1][2] = R+D;

	//Create up road
	glPushMatrix();
	glColor3f(1.0, 0.9, 0.0);
	glBegin(GL_QUAD_STRIP);
	glVertex2f(-L/2,R);
	glVertex2f(L,R);
	glVertex2f(-L/2,R+D);
	glVertex2f(L,R+D);
	glEnd();
	glPopMatrix();
	turns[2][0] = -L;
	turns[2][1] = R;
	turns[2][2] = R+D;

	//Draw left half circle
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	TwoSemiCirclesVertexes(-L,0,R,R+D,num_segments,false);
	glEnd();
	glPopMatrix();
	turns[3][0] = -L;
	turns[3][1] = -R-D;
	turns[3][2] = -R;

	// Draw bridge
	bridge.Render(R,D,L);

	//Create Start Line
	float X = 0.0f;
	for(int i=0;i<7;i++){
		X += D/14;
		glColor3f(1.0,1.0,1.0);
		glRectf(-L/2,-R-X,-L/3,-R-X+D/14);
		X += D/14;	
	}

	// Draw vehicle
	test_car.Render(-L/2,-R-D,R,D,L);
	// test_car.Render(L,-R-D,R,D,L);

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
	bridge.Move(dt);
	if (!turning) {
		if (next_turn == 0) {
			test_car.ForwardRight(dt);
		}
		else {
			test_car.ForwardLeft(dt);
		}
		if (test_car.ReachedPosition(turns[next_turn][0],
																 turns[next_turn][1],
																 turns[next_turn][2])) 
		{
				turning = true;
				next_turn = (next_turn + 1) % 4;
		}
	}
	else {
		if (next_turn == 1) {
			test_car.TurnUp(R+D, dt);
		}
		else {
			test_car.TurnDown(R+D, dt);
		}
		if (test_car.ReachedPosition(turns[next_turn][0],
																 turns[next_turn][1],
																 turns[next_turn][2])) 
		{
				turning = false;
				next_turn = (next_turn + 1) % 4;
		}
	}
	glutPostRedisplay();
}



void Keyboard(int key,int x,int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
			test_car.SpeedDown(SPEED_UP);
			break;
		case GLUT_KEY_RIGHT:
			test_car.SpeedUp(SPEED_UP);
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
	//Parameter handling
	glShadeModel (GL_SMOOTH);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);
    
	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);

}

void MenuSelect(int choice)
{
	switch (choice) {
		default:
			break;
	}

}


