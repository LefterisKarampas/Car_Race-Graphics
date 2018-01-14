#ifndef _MODEL_H_
#define _MODEL_H_

#include <iostream>
#include <vector>
#include "Vector.h"

using namespace std;


class Model{
	vector<vector<Vector3<double> > >render_model_vertex;
	vector<vector<Vector3<double> > >render_model_normal;
	void ObjLoader(char *);
public:
	Model(char *);
	~Model();
	void Render();
};


#endif //_MODEL_H_