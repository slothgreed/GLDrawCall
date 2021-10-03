#ifndef CAMERA_H
#define CAMERA_H
#include "BDB.h"
enum CAMERA_TYPE
{
	CAMERA_TYPE_PERSPECTIVE,
	CAMERA_TYPE_ORTHO
};
class ICamera 
{
public:
	ICamera();
	virtual ~ICamera();
	void LookAt(const vec3& eye, const vec3& center, const vec3& up);
	void SetProject(const mat4x4 proj);
	virtual CAMERA_TYPE Type() = 0;
	const mat4x4& ViewMatrix() const { return m_View; }
	const mat4x4& Projection() const { return m_Project; }

	vec3 XDirection();
	vec3 YDirection();
	vec3 ZDirection();
	const vec3& Eye() { return m_eye; };
	const vec3& Center() { return m_center; };
	const vec3& Up() { return m_up; };
	const vec3& Direction() { return m_direction; }

	const float LookAtDistance() const { return m_distance; }

	virtual void FitToBDB(const BDB& bdb) = 0;
private:
	mat4x4 m_View;
	mat4x4 m_Project;

	vec3 m_eye;
	vec3 m_center;
	vec3 m_up;
	vec3 m_direction;

	
	float m_distance;
};

#endif CAMERA_H