#include "Sphere.h"

Sphere::Sphere(const SphereArgs& args)
{
	Build(args);
}

Sphere::~Sphere()
{
}

void Sphere::Build(const SphereArgs& args)
{
	using namespace glm;
	float sliceStep = 2 * pi<float>() / args.slices;
	float stackStep = pi<float>() / args.stacks;
	float lengthInvert = 1.0f / args.radius;

	for (int i = 0; i <= args.stacks; i++)
	{
		float stackAngle = pi<float>() / 2 - i * stackStep;
		float xy = args.radius * cosf(stackAngle);

		for (int j = 0; j <= args.slices; j++)
		{
			float sectorAngle = j * sliceStep;
			vec3 position;
			position.x = xy * cosf(sectorAngle);
			position.y = xy * sinf(sectorAngle);
			position.z = args.radius * sinf(stackAngle);
			m_position.push_back(position);

			vec3 normal;
			normal.x = position.x * lengthInvert;
			normal.y = position.y * lengthInvert;
			normal.z = position.z * lengthInvert;
			m_normal.push_back(normal);

			//vec2 texcoord;
			//texcoord.x = (float)j / args.slices;
			//texcoord.y = (float)i / args.stacks;
			//m_texcoord.push_back(texcoord);
		}
	}

	for (int i = 0; i < args.stacks; i++)
	{
		int k1 = i * (args.slices + 1);
		int k2 = k1 + args.slices + 1;

		for (int j = 0; j < args.slices; j++)
		{
			if (i != 0)
			{
				m_index.push_back(k1);
				m_index.push_back(k2);
				m_index.push_back(k1 + 1);
			}

			if (i != args.stacks - 1)
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

