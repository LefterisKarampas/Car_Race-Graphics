#ifndef _MODEL_H_
#define _MODEL_H_

#include <iostream>
#include <vector>

using namespace std;

class Vertex{
	double x;
	double y;
	double z;
public:
	Vertex(double,double,double);
	~Vertex();
	double Get_x();
	double Get_y();
	double Get_z();
};

class Face{
	int p1;
	int p2;
	int p3;
public:
	Face(int,int,int);
	~Face();
	int Get_p1();
	int Get_p2();
	int Get_p3();
};


class Model{
	vector<Vertex> *vertices;
	vector<Face> *faces;
public:
	Model(vector<Vertex> *,vector<Face> *);
	~Model();
	vector<Vertex> * Get_Vertices();
	vector<Face> * Get_Faces();
};

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

#endif //_MODEL_H_