#include "../include/Model.h"
#include "../include/traffic_light.h"
#include "GL/freeglut.h"   // - An interface and windows management library
#include <math.h>

void drawCircle(GLfloat x, GLfloat y, GLfloat radius)
{
	int i;
	int triangleAmount = 1000; 
	GLfloat twicePi = 2.0f * M_PI;

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(5.0);

	glBegin(GL_LINES);
	for(i = 0; i <= triangleAmount; i++)
	{
	glVertex2f( x, y);
	glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
	}
	glEnd();
}


traffic_light::traffic_light(char *input_file,double R,double D){
	this->model = new Model(input_file);
	this->R = R;
	this->D = D;
}

traffic_light::~traffic_light(){
	delete this->model;
}

void traffic_light::Render(char color){

	glPushMatrix();
	glTranslatef(0,0,-(R+D+10));
	glScalef(3,3,3);
	//Draw traffic_light
	glPushMatrix();
	glColor3f(0.3f, 0.3f, 0.3f);
	//glRotatef(90,0.0,1.0,0.0);
	this->model->Render();
	glPopMatrix();

	//Draw green light
	if(color == 'g')
		glColor3f(0.0,1.0,0.0);
	else
		glColor3f(0.0,0.0,0.0);
	drawCircle(0,30,1.5);

	//Draw orange light
	if(color == 'o')
		glColor3f(1.0,0.5,0.0);
	else
		glColor3f(0.0,0.0,0.0);
	drawCircle(0,34,1.5);

	//Draw red light
	if(color == 'r')
		glColor3f(1.0,0.0,0.0);
	else
		glColor3f(0.0,0.0,0.0);
	drawCircle(0,38,1.5);

	glPopMatrix();
}