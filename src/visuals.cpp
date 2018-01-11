#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "GL/freeglut.h"   // - An interface and windows management library
#include "../include/visuals.h"   // Header file for our OpenGL functions
#include "../include/Model.h"
#include "../include/custom_vertexes.h"
#include "../include/bridge.h"

#define BRIDGE_SPEED 0.01

using namespace std;


std::vector<Model *> models;

extern char * car;
extern char * trafficlight;
double z = 0;


float zoom = 150.0f;

int dt = 1;

//Grid parameters
double R = 100.0f;	//radius
double D = 100.0f;	
double L = 150.0f;	//length

//Bridge object
Bridge bridge(BRIDGE_SPEED);

void DrawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_STRIP);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * M_PI * float(ii) / float(num_segments);//get the current angle 
        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component
        if(cx > 0){
        	if(x+cx < cx){
		       continue;
		    	}
        }
        else {
	    	if(x+cx > cx){
	       		continue;
	      }
	    }
        glVertex2f(x + cx, y + cy);//output vertex 
    }
    glEnd();
}

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

	int num_segments = 5000;
	//Draw right half circle
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	TwoSemiCirclesVertexes(L,0,R,R+D,num_segments,true);
	glEnd();
	glPopMatrix();

	//Draw left half circle
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	TwoSemiCirclesVertexes(-L,0,R,R+D,num_segments,false);
	glEnd();
	glPopMatrix();

	// Create bridge
	bridge.Render(R,D,L);

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
	
	//Create down road
	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	glVertex2f(-L,-R-D);
	glVertex2f(L,-R-D);
	glVertex2f(-L,-R);
	glVertex2f(L,-R);
	glEnd();
	glPopMatrix();


	//Create Start Line
	float X = 0.0f;
	for(int i=0;i<7;i++){
		X += D/14;
		glColor3f(1.0,1.0,1.0);
		glRectf(-L/2,-R-X,-L/3,-R-X+D/14);
		X += D/14;	
	}

	
	//DisplayModel((*models[0]),-L/1.5,-R-3*D/14,0);
	//DisplayModel((*models[0]),-L/1.5,-R-8*D/14,0);

	glPopMatrix();

	glutSwapBuffers();             // All drawing commands applied to the 
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
	glutPostRedisplay();
}



void Keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
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
	//Read model
	/*ReadModel(input_file);
	if(input_file2 != NULL)
		ReadModel(input_file2);
	*/
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

void ReadModel(char *object_file)
{

	ifstream obj_file(object_file);
	if (obj_file.fail()) 
		exit(1);
	vector<Vertex> *v = new vector<Vertex>();
	vector<Face> *f = new vector<Face>();
	char line[256];
	while(obj_file.good()){
		obj_file.getline(line,256);
		if(line[0] == 'v' && line[1] != 'n'){
			double x;
			double y;
			double z;
			sscanf(&(line[1]),"%lf %lf %lf",&x,&y,&z);
			Vertex vertex(x,y,z);
			v->push_back(vertex);
		}
		else if(line[0] == 'f'){
			int p1;
			int p2;
			int p3;
			if(sscanf(&(line[1]),"%d %d %d",&p1,&p2,&p3) != 3){
				int t1,t2,t3;
				if(sscanf(&(line[1]),"%d//%d %d//%d %d//%d",&p1,&t1,&p2,&t2,&p3,&t3) != 6){
					int z1,z2,z3;
					sscanf(&(line[1]),"%d/%d/%d %d/%d/%d %d/%d/%d",&p1,&t1,&z1,&p2,&t2,&z2,&p3,&t3,&z3);
				}
			}
			Face face(p1,p2,p3);
			f->push_back(face);
		}
		else{
			continue;
		}
	}
	obj_file.close();
	Model *md = new Model(v,f);
	models.push_back(md);
}

void DisplayModel(Model model,float x,float y,float z)
{

	glPushMatrix();
	glTranslatef(x,y,z);
	glScalef(0.3,0.3,0.3);
	glRotated(180,0,0,1);
	glColor3f(1.0,0.0,0.2);
	glBegin(GL_TRIANGLES);
	vector<Vertex> *v = model.Get_Vertices();
	vector<Face> * f = model.Get_Faces();
	for (unsigned int i = 0; i < f->size() ; i++)
	{
		int j = (*f)[i].Get_p1()-1;
		glVertex3f((*v)[j].Get_x(),(*v)[j].Get_y(),(*v)[j].Get_z());
		j = (*f)[i].Get_p2()-1;
		glVertex3f((*v)[j].Get_x(),(*v)[j].Get_y(),(*v)[j].Get_z());
		j = (*f)[i].Get_p3()-1;
		glVertex3f((*v)[j].Get_x(),(*v)[j].Get_y(),(*v)[j].Get_z());
	}
	glEnd();
	glPopMatrix();
} 
