#include "Cube.h"
Cube::Cube(const vec3& min, const vec3& max)
	:m_min(min), m_max(max)
{
	m_position.resize(8);
	m_position[0] = (m_min);
	m_position[1] = (vec3(m_max.x, m_min.y, m_min.z));
	m_position[2] = (vec3(m_max.x, m_max.y, m_min.z));
	m_position[3] = (vec3(m_min.x, m_max.y, m_min.z));

	m_position[4] = (vec3(m_min.x, m_min.y, m_max.z));
	m_position[5] = (vec3(m_max.x, m_min.y, m_max.z));
	m_position[6] = (m_max);
	m_position[7] = (vec3(m_min.x, m_max.y, m_max.z));

	m_index.resize(36);
	AddIndex(0, 0, 3, 2, 1);
	AddIndex(1, 0, 4, 7, 3);
	AddIndex(2, 4, 5, 6, 7);
	AddIndex(3, 1, 2, 6, 5);
	AddIndex(4, 2, 3, 7, 6);
	AddIndex(5, 1, 5, 4, 0);
	m_drawType = GL_TRIANGLES;
}

void Cube::AddIndex(int index, int vertex0, int vertex1, int vertex2, int vertex3)
{
	index *= 6;
	m_index[index + 0] = vertex0; m_index[index + 1] = vertex1; m_index[index + 2] = vertex2;
	m_index[index + 3] = vertex0; m_index[index + 4] = vertex2; m_index[index + 5] = vertex3;
}
