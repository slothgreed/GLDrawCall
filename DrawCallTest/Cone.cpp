#include "Cone.h"
Cone::Cone(float _radius, float _height, int _partition)
	: radius(_radius)
	, height(_height)
	, partition(_partition)
{
	m_position.push_back(vec3(0, height, 0));
	m_position.push_back(vec3(0, 0, 0));

	float rad = 2 * pi<float>() / partition;
	float theta = 0;

	float y = pi<float>() / 2;
	for (int i = 0; i <= partition; i++)
	{
		float x = -(i * rad);
		m_position.push_back(vec3(
			radius * sin(y) * cos(x),
			radius * cos(y),
			radius * sin(y) * sin(x)
		));
	}

	int index1;
	int index2;
	for (int i = 0; i <= partition; i++)
	{

		index1 = 2 + i;
		if (2 + i + 1 == m_position.size())
		{
			index2 = 2;
		}
		else
		{
			index2 = 2 + i + 1;
		}

		m_index.push_back(0);			// 先端点
		m_index.push_back(index1);
		m_index.push_back(index2);

		// 終端を結ぶ
		m_index.push_back(1);			// 底面の中心点
		m_index.push_back(index2);
		m_index.push_back(index1);
	}

	m_drawType = GL_TRIANGLES;
}
