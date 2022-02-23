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

void DrawElementsDrawer::BuildRenderItem(const Primitives& pPrimitive, std::vector<mat4x4>&& matrixs)
{
	m_pRenderItem.resize(pPrimitive.size());

	for (int i = 0; i < m_pRenderItem.size(); i++)
	{
		m_pRenderItem[i] = std::make_unique<RenderItem>(pPrimitive[i]);
	}

	m_matrixs = std::move(matrixs);
	m_pShader->Use();
}



void DrawElementsDrawer::Draw(const mat4x4& proj, const mat4x4& view)
{
	glEnableVertexAttribArray(ATTRIB_POSITION);
	glEnableVertexAttribArray(ATTRIB_NORMAL);

	m_pShader->SetViewProj(proj*view);

	int num = 0;
	while (num < m_matrixs.size())
	{
		for (int i = 0; i < m_pRenderItem.size(); i++)
		{
			m_pShader->SetModel(m_matrixs[num++]);
			auto& pItem = m_pRenderItem[i];

			pItem->PositionBuffer()->Bind();
			glVertexAttribPointer(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			pItem->NormalBuffer()->Bind();
			glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

			pItem->IndexBuffer()->Bind();
			glDrawElements(pItem->PrimitiveType(), pItem->IndexBuffer()->Size(), GL_UNSIGNED_INT, 0);
		}
	}
}