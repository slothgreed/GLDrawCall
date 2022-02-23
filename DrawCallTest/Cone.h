#ifndef CONE_H
#define CONE_H

#include "IPrimitive.h"
class Cone : public IPrimitive
{
public:
	Cone(float _radius, float _height, int _partition);
	~Cone() {};

private:
	// radius = x around;
	// height = y value;
	float radius;
	float height;
	int partition;

};
#endif CONE_H
