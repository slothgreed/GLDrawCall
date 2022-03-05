#include "BeginEndDrawer.h"
BeginEndDrawer::BeginEndDrawer()
{
}

BeginEndDrawer::~BeginEndDrawer()
{
}

void BeginEndDrawer::BuildRenderItem(const Primitives& pPrimitive, std::vector<mat4x4>&& matrixs)
{
	m_pPrimitives = pPrimitive;
	m_matrix = std::move(matrixs);
}

void BeginEndDrawer::Draw(const mat4x4& proj, const mat4x4& view)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(&(proj*view)[0][0]);
	

	glMatrixMode(GL_MODELVIEW);
	OUTPUT_GLERROR;
	int num = 0;
	while (num < m_matrix.size())
	{
		for (int i = 0; i < m_pPrimitives.size(); i++)
		{
			glLoadIdentity();
			glMultMatrixf(&(m_matrix[num++][0][0]));
			glBegin(GL_TRIANGLES);
			OUTPUT_GLERROR;
			for (int j = 0; j < m_pPrimitives[i]->Index().size(); j++)
			{
				int index = m_pPrimitives[i]->Index()[j];
				auto& nor = m_pPrimitives[i]->Normal()[index];
				auto& pos = m_pPrimitives[i]->Position()[index];
				glColor3d(nor.x, nor.y, nor.z);
				glVertex3d(pos.x, pos.y, pos.z);
			}
			glEnd();
		}
	}

	OUTPUT_GLERROR;
}
