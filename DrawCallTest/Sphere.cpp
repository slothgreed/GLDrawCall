#include "Sphere.h"

Sphere::Sphere(const glm::vec3& _position, float _radius, int _slices, int _stacks) :
	position(_position), radius(_radius), slices(_slices), stacks(_stacks)
{
	using namespace glm;
	float sliceStep = 2 * pi<float>() / slices;
	float stackStep = pi<float>() / stacks;
	float lengthInvert = 1.0f / radius;

	for (int i = 0; i <= stacks; i++)
	{
		float stackAngle = pi<float>() / 2 - i * stackStep;
		float xy = radius * cosf(stackAngle);

		for (int j = 0; j <= slices; j++)
		{
			float sectorAngle = j * sliceStep;
			m_position.push_back(vec3(
				xy * cosf(sectorAngle),
				xy * sinf(sectorAngle),
				radius * sinf(stackAngle)));

			m_normal.push_back(vec3(
				m_position[m_position.size() - 1].x * lengthInvert,
				m_position[m_position.size() - 1].y * lengthInvert,
				m_position[m_position.size() - 1].z * lengthInvert));
		}
	}

	for (int i = 0; i < stacks; i++)
	{
		int k1 = i * (slices + 1);
		int k2 = k1 + slices + 1;

		for (int j = 0; j < slices; j++)
		{
			if (i != 0)
			{
				m_index.push_back(k1);
				m_index.push_back(k2);
				m_index.push_back(k1 + 1);
			}

			if (i != stacks - 1)
			{
				m_index.push_back(k1 + 1);
				m_index.push_back(k2);
				m_index.push_back(k2 + 1);
			}

			k1++;
			k2++;
		}
	}

	m_drawType = GL_TRIANGLES;
}

