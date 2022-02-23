#ifndef SPHERE_H
#define SPHERE_H

#include "IPrimitive.h"

class Sphere : public IPrimitive
{
public:
	Sphere(float _radius, int _slices, int _stacks);
	~Sphere() {};


private:
	float radius;
	int slices;	// z around;
	int stacks;	// z along;
};
#endif SPHERE_H
