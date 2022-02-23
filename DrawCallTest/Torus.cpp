#include "Torus.h"

Torus::Torus(float _inRad, float _outRad, int _nsides, int _rings) 
	: inRad(_inRad)
	, outRad(_outRad)
	, nsides(_nsides)
	, rings(_rings)
{
	float sideAngle = pi<float>() * 2 / nsides;
	float ringAngle = pi<float>() * 2 / rings;
	for (int i = 0; i <= nsides; i++)
	{
		float r = sideAngle * i;
		float rr = (float)cos(r);
		float ry = (float)sin(r);

		for (int j = 0; j <= rings; j++)
		{
			float tr = ringAngle * j;
			float tx = (rr * inRad + outRad) * (float)cos(tr);
			float ty = ry * inRad;
			float tz = (rr * inRad + outRad) * (float)sin(tr);
			m_position.push_back(vec3(tx, ty, tz));

			float rx = rr * (float)cos(tr);
			float rz = rr * (float)sin(tr);
			m_normal.push_back(vec3(rx, ry, rz));

			if (i != nsides && j != rings) {
				int index = (rings + 1) * i + j;
				m_index.push_back(index);
				m_index.push_back(index + rings + 1);
				m_index.push_back(index + 1);

				m_index.push_back(index + rings + 1);
				m_index.push_back(index + rings + 2);
				m_index.push_back(index + 1);
			}
		}
	}
	
	m_drawType = GL_TRIANGLES;
}
