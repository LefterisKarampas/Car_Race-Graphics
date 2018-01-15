#ifndef _TRAFFIC_LIGHT_H_
#define _TRAFFIC_LIGHT_H_
#include "Model.h"

class traffic_light{
	Model *model;
	char color;
	double R;
	double D;
public:
	traffic_light(char *,double R,double D);
	~traffic_light();
	void Render(char);
};

#endif