#ifndef CYLINDER_H
#define CYLINDER_H
#include "IPrimitive.h"

class Cylinder : public IPrimitive
{
public:
	Cylinder(float _baseRad, float _topRad, float _height, int _slices);
	~Cylinder() {};

private:
	float baseRad;
	float topRad;
	float height;
	int slices;

};
#endif CYLINDER_H