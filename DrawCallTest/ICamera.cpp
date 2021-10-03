#include "ICamera.h"
ICamera::ICamera()
{
}

ICamera::~ICamera()
{
}

void ICamera::LookAt(const vec3& eye, const vec3& center, const vec3& up)
{
	m_View = glm::lookAt(eye, center, up);
	m_eye = eye;
	m_center = center;
	m_up = up;
	m_direction = glm::normalize(m_eye - m_center);
	m_distance = glm::length(m_eye - m_center);
}

void ICamera::SetProject(mat4x4 proj)
{
	m_Project = proj;
}

vec3 ICamera::XDirection()
{
	return vec3(m_View[0].x, m_View[1].x, m_View[2].x);
}

vec3 ICamera::YDirection()
{
	return vec3(m_View[0].y, m_View[1].y, m_View[2].y);
}
vec3 ICamera::ZDirection()
{
	return vec3(m_View[0].z, m_View[1].z, m_View[2].z);
}
