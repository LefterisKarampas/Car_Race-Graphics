#include "../include/Score.h"
#include "GL/freeglut.h"
#include <cstdio>
#include <cstring> 


Score::Score(){
	this->home_score = 0;
	this->away_score = 0;
}

Score::~Score(){
	;
}

void Score::Render(float board_rotate){
	char str[128];
	sprintf(str,"Score: %d - %d",this->home_score,this->away_score);
	glPushMatrix();
	glTranslatef(50,0,-200);
	glScalef(4,4,4);
	glRotatef(-20+board_rotate,1,0,0);
	//glRotatef(-20,0,1,0);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(20,20);
	glVertex2f(20,40);
	glVertex2f(100,40);
	glVertex2f(100,20);
	glEnd();
	glColor3f(0.0,1.0,1.0);
	glTranslatef(30,28.0,0.0);
	GLfloat size = 0.05f;
	glScalef(size,size,size);
	for (int i=0;i<strlen(str);i++){
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
	}
	glPopMatrix();
}

void Score::home(){
	this->home_score++;
}

void Score::away(){
	this->away_score++;
}

void Score::Reset(){
	this->home_score = 0;
	this->away_score = 0;
}

int Score::GetHome() {
	return home_score;
}

int Score::GetAway() {
	return away_score;
}

int Score::SetHome(int home) {
	home_score = home;
}

int Score::SetAway(int away) {
	away_score = away;
}