#include "DrawElementsDrawer.h"
#include "RenderItem.h"
#include "SimpleShader.h"
DrawElementsDrawer::DrawElementsDrawer()
	:IDrawer(std::make_unique<SimpleShader>())
{
}

DrawElementsDrawer::~DrawElementsDrawer()
{

}

void DrawElementsDrawer::BuildRenderItem(std::shared_ptr<IPrimitive> pPrimitive, int range)
{
	m_pRenderItem.resize(range*range*range);
	for (int x = 0; x < range; x++)
	{
		for (int y = 0; y < range; y++)
		{
			for (int z = 0; z < range; z++)
			{
				int index = x * range * range + y * range + z;
				mat4x4 matrix = glm::translate(mat4x4(1), vec3(x, y, z));
				m_pRenderItem[index] = (std::make_unique<RenderItem>(pPrimitive, matrix));
				//fprintf(stdout, "%d,%d,%d\n", x, y, z);
			}
		}
	}

	m_pShader->Use();
}



void DrawElementsDrawer::Draw(const mat4x4& proj, const mat4x4& view)
{
	//
	//glVertexAttribFormat(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0);
	//glVertexAttribFormat(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, 0);
	//glVertexAttribBinding(ATTRIB_POSITION, 0);
	//glVertexAttribBinding(ATTRIB_NORMAL, 0);

	glEnableVertexAttribArray(ATTRIB_POSITION);
	glEnableVertexAttribArray(ATTRIB_NORMAL);

	m_pShader->SetViewProj(proj*view);
	for (int i = 0; i < m_pRenderItem.size(); i++)
	{
		auto pItem = (RenderItem*)m_pRenderItem[i].get();
		m_pShader->SetModel(pItem->ModelMatrix());

		if (pItem->IsInterleave())
		{
			pItem->VertexBuffer()->Bind();
			glVertexAttribPointer(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
			glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_normal));
		}
		else
		{
			pItem->PositionBuffer()->Bind();
			glVertexAttribPointer(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			pItem->NormalBuffer()->Bind();
			glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		}

		pItem->IndexBuffer()->Bind();


		//glBindVertexBuffer(ATTRIB_POSITION, pItem->PositionBuffer()->GetId(), 0, sizeof(glm::vec3));
		//glBindVertexBuffer(ATTRIB_NORMAL, pItem->NormalBuffer()->GetId(), 0, sizeof(glm::vec3));

		glDrawElements(pItem->GetDrawType(), pItem->IndexBuffer()->Size(), GL_UNSIGNED_INT, 0);
	}
}