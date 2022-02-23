#ifndef CUBE_H
#define CUBE_H
#include "IPrimitive.h"
class Cube : public IPrimitive
{
public:
	Cube(const vec3& min, const vec3& max);
	~Cube() {};

private:
	vec3 m_min;
	vec3 m_max;

	void AddIndex(int index, int vertex0, int vertex1, int vertex2, int vertex3);

};
#endif CUBE_H
