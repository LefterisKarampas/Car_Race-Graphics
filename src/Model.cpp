#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/Model.h"
#include "../include/Vector.h"
#include "Vector.cpp"
#include "GL/freeglut.h"   // - An interface and windows management library
using namespace std;



//Model Functionality
Model::Model(char *path){
	this->ObjLoader(path);
}

Model::~Model(){
}

void Model::ObjLoader(char *path){
	ifstream in(path);
	if(!in.is_open()){
		cerr << "Failed load object from " << path << " file";
		return;
	}
	vector<Vector3<double> >  *vertices;
	vector<Vector3<double> >  *normal;
	vector<Vector3<int> >  *face_vertices;
	vector<Vector3<int> >  *face_normal;
	vertices = new vector<Vector3<double> >();
	face_vertices = new vector<Vector3<int> >();
	face_normal = new vector<Vector3<int> >();
	normal = new vector<Vector3<double> > ();
	string line;
	char id;
	while(getline(in,line)){
		if(line[0] == 'f'){
			int i=2;
			int flag = 0;
			int continous = 0;
			while(i < line.size()){
				if((line[i] == ' ' || line[i] == '\t')){
					break;
				}
				else if(line[i] == '/'){
					flag++;
					if(line[i-1] == line[i]){
						continous = 1;
					}
				}
				i++;
			}
			if(flag == 0){
				int v[3];
				sscanf(line.c_str(),"%c %d %d %d",&id,v,v+1,v+2);
				face_vertices->push_back(Vector3<int>(v[0]-1,v[1]-1,v[2]-1));
			}
			else if(flag == 1){
				int v[3];
				int t[3];
				sscanf(line.c_str(),"%c %d/%d %d/%d %d/%d",&id,v,t,v+1,t+1,v+2,t+2);
				face_vertices->push_back(Vector3<int>(v[0]-1,v[1]-1,v[2]-1));
			}
			else if(flag == 2){
				if(continous == 1){
					int v[3];
					int n[3];
					sscanf(line.c_str(),"%c %d//%d %d//%d %d//%d",&id,v,n,v+1,n+1,v+2,n+2);
					face_vertices->push_back(Vector3<int>(v[0]-1,v[1]-1,v[2]-1));
					face_normal->push_back(Vector3<int>(n[0]-1,n[1]-1,n[2]-1));
				}
				else{
					int v[3];
					int t[3];
					int n[3];
					sscanf(line.c_str(),"%c %d/%d/%d %d/%d/%d %d/%d/%d",&id,v,t,n,v+1,t+1,n+1,v+2,t+2,n+2);
					face_vertices->push_back(Vector3<int>(v[0]-1,v[1]-1,v[2]-1));
					face_normal->push_back(Vector3<int>(n[0]-1,n[1]-1,n[2]-1));
				}
			}
		}
		else if(line[0] == 'v' && line[1] == ' '){
			double v[3];
			sscanf(line.c_str(),"%c %lf %lf %lf",&id,v,v+1,v+2);
			vertices->push_back(Vector3<double>(v[0],v[1],v[2]));
		}
		else if(line[0] == 'v' && line[1] == 'n'){
			double vn[3];
			sscanf(line.c_str(),"%c %lf %lf %lf",&id,vn,vn+1,vn+2);
			normal->push_back(Vector3<double>(vn[0],vn[1],vn[2]));
		}
	}
	for(int i=0;i<face_vertices->size();i++){
		Vector3<double> x = vertices->at(face_vertices->at(i).Get_x());
		Vector3<double> y = vertices->at(face_vertices->at(i).Get_y());
		Vector3<double> z = vertices->at(face_vertices->at(i).Get_z());
		vector<Vector3<double> > t;
		t.push_back(x);
		t.push_back(y);
		t.push_back(z);
		this->render_model_vertex.push_back(t);
	}
	for(int i=0;i<face_normal->size();i++){
		Vector3<double> x = normal->at(face_normal->at(i).Get_x());
		Vector3<double> y = normal->at(face_normal->at(i).Get_y());
		Vector3<double> z = normal->at(face_normal->at(i).Get_z());
		vector<Vector3<double> > t;
		t.push_back(x);
		t.push_back(y);
		t.push_back(z);
		this->render_model_normal.push_back(t);
	}
	delete vertices;
	delete normal;
	delete face_vertices;
	delete face_normal;

}

void Model::Render(){
	glPushMatrix();
	for(unsigned int i=0;i<this->render_model_vertex.size();i++){
		glBegin(GL_TRIANGLES);
		for(unsigned int j=0;j<this->render_model_vertex.at(i).size();j++){
			glVertex3f(this->render_model_vertex.at(i).at(j).Get_x(),this->render_model_vertex.at(i).at(j).Get_y(),
				this->render_model_vertex.at(i).at(j).Get_z());
		}
		glEnd();
	}
	for(unsigned int i=0;i<this->render_model_normal.size();i++){
		glBegin(GL_TRIANGLES);
		for(unsigned int j=0;j<this->render_model_normal.at(i).size();j++){
			glNormal3f(this->render_model_normal.at(i).at(j).Get_x(),this->render_model_normal.at(i).at(j).Get_y(),
				this->render_model_normal.at(i).at(j).Get_z());
		}
		glEnd();
	}
	glPopMatrix();
}
