#include "../include/Model.h"
#include <vector>
#include <iostream>

using namespace std;


//Vertex Functionality
Vertex::Vertex(double x,double y,double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

Vertex::~Vertex(){};

double Vertex::Get_x(){
	return this->x;
}


double Vertex::Get_y(){
	return this->y;
}

double Vertex::Get_z(){
	return this->z;
}



//Face Functionality
Face::Face(int p1,int p2,int p3){
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
}

Face::~Face(){};

int Face::Get_p1(){
	return this->p1;
}


int Face::Get_p2(){
	return this->p2;
}

int Face::Get_p3(){
	return this->p3;
}


//Model Functionality
Model::Model(vector<Vertex> *v,vector<Face> *f){
	this->vertices = v;
	this->faces = f;
}

Model::~Model(){
	delete this->vertices;
	delete this->faces;
}

vector<Vertex> * Model::Get_Vertices(){
	return this->vertices;
}

vector<Face> * Model::Get_Faces(){
	return this->faces;
}