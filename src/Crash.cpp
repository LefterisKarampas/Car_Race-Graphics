#include "../include/Crash.h"
#include "GL/freeglut.h"
#include <cstring>
#include <cstdio>


Crash::Crash(){
	;
}

Crash::~Crash(){
	;
}

void Crash::Render(float rot)
{
	glPushMatrix();
	glRotatef(rot,1,0,0);

	glPushMatrix();
	glScalef(5.0,5.0,5.0);
	glColor3f(1.0,0.8,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.0,1.0);	//v0
	glVertex2f(1.0,1.7);	//v1
	glVertex2f(1.5,0.6);	//v2
	glVertex2f(2.5,0.7);	//v3
	glVertex2f(2.0,0.0);	//v4
	glVertex2f(2.5,-0.7);	//v5
	glVertex2f(1.3,-0.7);	//v8
	glVertex2f(0.8,-1.7);	//v9
	
	glVertex2f(0.0,-1.0);	//v10
	
	glVertex2f(-0.8,-1.7);	//v11
	glVertex2f(-1.3,-0.7);	//v12
	glVertex2f(-2.5,-0.9);	//v13
	glVertex2f(-1.5,0.0);	//v14
	glVertex2f(-2.2,0.9);	//v15
	glVertex2f(-1.2,0.7);	//v16
	glVertex2f(-0.7,1.7);	//v17
	glEnd();
	glPopMatrix();

	const char str[] = "Crash!";
	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glTranslatef(-7.8,-2.0,0.0);
	GLfloat size = 0.05f;
	glScalef(size,size,size);
	for (int i=0;i<strlen(str);i++)
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
	glPopMatrix();

	glPopMatrix();

}
