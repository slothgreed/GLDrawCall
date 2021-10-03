#include "OrthoCamera.h"
OrthoCamera::OrthoCamera()
{
}

OrthoCamera::~OrthoCamera()
{
}

void OrthoCamera::Ortho(float left, float right, float bottom, float top, float _near, float _far)
{
	SetProject(glm::ortho(left, right, bottom, top, _near, _far));
	m_ortho.m_left = left;
	m_ortho.m_right = right;
	m_ortho.m_bottom = bottom;
	m_ortho.m_top = top;
	m_ortho.m_near = _near;
	m_ortho.m_far = _far;
}

void OrthoCamera::Ortho(const OrthoCamera::OrthoParameter& parameter)
{
	Ortho(parameter.m_left,
		parameter.m_right,
		parameter.m_bottom,
		parameter.m_top,
		parameter.m_near,
		parameter.m_far);
}

void OrthoCamera::GetOrtho(OrthoCamera::OrthoParameter *parameter)
{
	*parameter = m_ortho;
}

float OrthoCamera::GetWidth()
{
	assert(m_ortho.m_right > m_ortho.m_left);
	return m_ortho.m_right - m_ortho.m_left;
}

float OrthoCamera::GetHeight()
{
	assert(m_ortho.m_top > m_ortho.m_bottom);
	return m_ortho.m_top - m_ortho.m_bottom;
}

float OrthoCamera::GetDepth()
{
	assert(m_ortho.m_far > m_ortho.m_near);
	return m_ortho.m_far - m_ortho.m_near;
}

vec3 OrthoCamera::GetCenter()
{
	return vec3(
		(m_ortho.m_left + m_ortho.m_right) * 0.5,
		(m_ortho.m_bottom + m_ortho.m_top) * 0.5,
		(m_ortho.m_near + m_ortho.m_far) * 0.5);
}

void OrthoCamera::FitToBDB(const BDB& bdb)
{
	Ortho(
		bdb.Min().x,
		bdb.Max().x,
		bdb.Min().y,
		bdb.Max().y,
		bdb.Min().z,
		bdb.Max().z);
}
