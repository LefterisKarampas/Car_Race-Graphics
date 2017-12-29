#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>

#include "GL/freeglut.h"   // - An interface and windows management library
#include "../include/visuals.h"   // Header file for our OpenGL functions
#include "../include/Model.h"

std::vector<Model *> models;
static float tx = 0.0;
static float rotx = 0.0;
static bool animate = false;
static float red = 1.0;
static float green = 0.0;
static float blue = 0.0;

extern char * input_file;
extern char * input_file2;
double z = 0;

using namespace std;

void keimeno(const char *str,float size)
{

	glPushMatrix();
	glScalef(size,size,size);

	for (int i=0;i<strlen(str);i++)
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
	glPopMatrix();

}

void Render()
{    
  //CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
													   // and the depth buffer
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();
	
 
  
              
  for(unsigned int i=0;i<models.size();i++){
  	 glTranslatef(0.0,0.0,-100.0);
  	 glRotatef(30,1,0,0);
  	DisplayModel((*models[i]));
  }

 
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
  gluPerspective(60.0, (float)w/(float)h, 1.0, 500.0);
}



void Idle()
{

	;//glutPostRedisplay();
}



void Keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 'a':{
			z-= 100.0;
			break;
		}
		case 'd':{
			z+= 100.0;
			break;
		}
		default: 
			return;
	}
	//glutPostRedisplay();

}

void Mouse(int button,int state,int x,int y)
{
	 if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	 {
         ;//glutPostRedisplay();
	 }
}


void Setup()  // TOUCH IT !! 
{ 
	ReadModel(input_file);
	if(input_file2 != NULL)
		ReadModel(input_file2);

	//Parameter handling
	glShadeModel (GL_SMOOTH);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);
    
	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
  
	//Set up light source
	GLfloat light_position[] = { 0.0, 30.0, 50.0, 0.0 };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position);

	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

	   
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	//01
	glFrontFace(GL_CCW);
 

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

void DisplayModel(Model model)
{

	glPushMatrix();
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
