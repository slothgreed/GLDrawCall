#include "Triangle.h"
Triangle::Triangle()
{
	Build();
}

Triangle::~Triangle()
{
}

void Triangle::Build()
{
	m_position.push_back(glm::vec3(-0.5, -0.5, 0.0));
	m_position.push_back(glm::vec3(0.5, -0.5, 0.0));
	m_position.push_back(glm::vec3(0.25, 0.5, 0.0));
	m_normal.push_back(glm::vec3(0.0, 0.0, 1.0));
	m_normal.push_back(glm::vec3(0.0, 0.0, 1.0));
	m_normal.push_back(glm::vec3(0.0, 0.0, 1.0));
	m_index.push_back(0);
	m_index.push_back(1);
	m_index.push_back(2);
	m_drawType = GL_TRIANGLES;
}