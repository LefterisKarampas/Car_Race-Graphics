#include "../include/Map.h"
#include "GL/freeglut.h"   // - An interface and windows management library
#include "../include/custom_vertexes.h"


Map::Map(double R,double D,double L){
	this->R = R;
	this->D = D;
	this->L = L;
}

Map::~Map(){
	;
}

void Map::Render(){

	glColor3f(0.0,0.0,1.0);
	//Create down road
	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	glVertex2f(-L,-R-D);
	glVertex2f(L,-R-D);
	glVertex2f(-L,-R);
	glVertex2f(L,-R);
	glEnd();
	glPopMatrix();

	int num_segments = 5000;
	//Draw right half circle
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	TwoSemiCirclesVertexes(L,0,R,R+D,num_segments,true);
	glEnd();
	glPopMatrix();

	//Create up road
	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	glVertex2f(-L/2,R);
	glVertex2f(L,R);
	glVertex2f(-L/2,R+D);
	glVertex2f(L,R+D);
	glEnd();
	glPopMatrix();

	//Draw left half circle
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	TwoSemiCirclesVertexes(-L,0,R,R+D,num_segments,false);
	glEnd();
	glPopMatrix();

	//Create Start Line
	glColor3f(1.0,1.0,1.0);
	float X = 0.0f;
	for(int i=0;i<7;i++){
		X += D/14;
		glRectf(-L/2,-R-X,-L/3,-R-X+D/14);
		X += D/14;	
	}
}
