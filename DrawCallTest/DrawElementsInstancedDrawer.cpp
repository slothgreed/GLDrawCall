#include "DrawElementsInstancedDrawer.h"
#include "InstanceShader.h"
#include "RenderItem.h"
DrawElementsInstancedDrawer::DrawElementsInstancedDrawer()
	:IDrawer(std::make_unique<InstanceShader>())
{
}

DrawElementsInstancedDrawer::~DrawElementsInstancedDrawer()
{
}

void DrawElementsInstancedDrawer::BuildRenderItem(std::shared_ptr<IPrimitive> pPrimitive, int range)
{
	m_pRenderItem.resize(1);
	std::vector<mat4> m_matrices(range*range*range);
	for (int x = 0; x < range; x++)
	{
		for (int y = 0; y < range; y++)
		{
			for (int z = 0; z < range; z++)
			{
				int index = x * range * range + y * range + z;
				m_matrices[index] = glm::translate(mat4x4(1), vec3(x, y, z));
				//fprintf(stdout, "%d,%d,%d\n", x, y, z);
			}
		}
	}
	OUTPUT_GLERROR;

	m_pShader->SetModels(m_matrices);
	OUTPUT_GLERROR;
	m_pRenderItem[0] = std::make_unique<RenderItem>(pPrimitive, mat4x4(1));
	m_objectNum = range * range * range;
}

void DrawElementsInstancedDrawer::Draw(const mat4x4& proj, const mat4x4& view)
{
	OUTPUT_GLERROR;
	glEnableVertexAttribArray(ATTRIB_POSITION);
	glEnableVertexAttribArray(ATTRIB_NORMAL);
	glEnableVertexAttribArray(ATTRIB_MATRIX);
	OUTPUT_GLERROR;

	glVertexBindingDivisor(ATTRIB_POSITION, 0);
	glVertexBindingDivisor(ATTRIB_NORMAL, 0);
	glVertexBindingDivisor(ATTRIB_MATRIX, 1);
	OUTPUT_GLERROR;

	m_pShader->Use();

	m_pShader->SetViewProj(proj*view);
	auto pItem = (RenderItem*)m_pRenderItem[0].get();
	if (pItem->IsInterleave())
	{
		glVertexAttribFormat(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribFormat(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex,m_normal));
		glVertexAttribIFormat(ATTRIB_MATRIX, 1, GL_INT, 0);
		glBindVertexBuffer(ATTRIB_POSITION, pItem->VertexBuffer()->GetId(), 0, sizeof(Vertex));
		glBindVertexBuffer(ATTRIB_NORMAL, pItem->VertexBuffer()->GetId(), 0, sizeof(Vertex));
	}
	else
	{
		glVertexAttribFormat(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribFormat(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribIFormat(ATTRIB_MATRIX, 1, GL_INT, 0);
		glBindVertexBuffer(ATTRIB_POSITION, pItem->PositionBuffer()->GetId(), 0, sizeof(glm::vec3));
		glBindVertexBuffer(ATTRIB_NORMAL, pItem->NormalBuffer()->GetId(), 0, sizeof(glm::vec3));
	}
	OUTPUT_GLERROR;

	pItem->IndexBuffer()->Bind();
	glDrawElementsInstanced(pItem->GetDrawType(), pItem->IndexBuffer()->Size(), GL_UNSIGNED_INT, 0, m_objectNum);
	OUTPUT_GLERROR;
}