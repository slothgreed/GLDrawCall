#ifndef TORUS_H
#define TORUS_H

#include "IPrimitive.h"
class Torus : public IPrimitive
{
public:
	Torus(float _inRad, float _outRad, int _nsides, int _rings);
	~Torus() {};
private:

	float inRad;
	float outRad;
	int nsides;
	int rings;
};

#endif TORUS_H
