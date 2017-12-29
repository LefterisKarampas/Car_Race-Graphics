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

#endif //_MODEL_H_