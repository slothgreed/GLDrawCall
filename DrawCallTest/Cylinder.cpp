#include "Cylinder.h"
Cylinder::Cylinder(float _baseRad, float _topRad, float _height, int _slices)
	: baseRad(_baseRad)
	, topRad(_topRad)
	, height(_height)
	, slices(_slices)
{
	m_position.push_back(vec3(0, 0, 0));
	m_position.push_back(vec3(0, height, 0));
	
	float sliceStep = 2 * glm::pi<float>() / slices;
	float angle = 0;
	for (int i = 0; i < slices; i++)
	{
		angle = i * sliceStep;
		float cosAngle = cos(angle);
		float sinAngle = sin(angle);
		float xPos = cosAngle * baseRad;
		float yPos = 0;
		float zPos = sinAngle * baseRad;
		m_position.push_back(vec3(xPos, yPos, zPos));

		xPos = cosAngle * topRad;
		yPos = height;
		zPos = sinAngle * topRad;
		m_position.push_back(vec3(xPos, yPos, zPos));
	}
	
	// ��ʒ��_ => ��ʒ��_�̏��ō쐬
	// k = 0 < ��ʁE��ʕ�;
	int k = 2;
	for (int i = 0; i < slices - 1; i++)
	{
		// ���
		m_index.push_back(0);
		m_index.push_back(k);
		m_index.push_back(k + 2);

		// ���
		m_index.push_back(1);
		m_index.push_back(k + 3);
		m_index.push_back(k + 1);

		//// ����
		m_index.push_back(k);
		m_index.push_back(k + 1);
		m_index.push_back(k + 2);
						  
		m_index.push_back(k + 2);
		m_index.push_back(k + 1);
		m_index.push_back(k + 3);
		k += 2;
	}

	// ���
	m_index.push_back(0);
	m_index.push_back(k);
	m_index.push_back(2);

	// ���
	m_index.push_back(1);
	m_index.push_back(3);
	m_index.push_back(k + 1);

	//// ����
	m_index.push_back(k);
	m_index.push_back(k + 1);
	m_index.push_back(2);

	m_index.push_back(k + 1);
	m_index.push_back(3);
	m_index.push_back(2);

	CalcNormal();

	m_drawType = GL_TRIANGLES;
}
