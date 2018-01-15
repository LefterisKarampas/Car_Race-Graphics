#ifndef _TRAFFIC_LIGHT_H_
#define _TRAFFIC_LIGHT_H_
#include "Model.h"

class traffic_light{
	Model *model;
	char color;
public:
	traffic_light(char *);
	~traffic_light();
	void Render(char);
};

#endif