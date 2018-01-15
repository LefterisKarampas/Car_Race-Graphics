#ifndef _MAP_H_
#define _MAP_H_

class Map{
	double L;
	double R;
	double D;
public:
	Map(double,double,double);
	~Map();
	void Render();
};

#endif