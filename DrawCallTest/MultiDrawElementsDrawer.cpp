#include "MultiDrawElementsDrawer.h"
#include "MultiRenderItem.h"
#include "SimpleShader.h"
MultiDrawElementsDrawer::MultiDrawElementsDrawer()
	:IDrawer(std::make_unique<SimpleShader>())
{
}

MultiDrawElementsDrawer::~MultiDrawElementsDrawer()
{
}

void MultiDrawElementsDrawer::BuildRenderItem(const Primitives& pPrimitive, std::vector<mat4x4>&& matrixs)
{
	m_pRenderItem.resize(1);
	std::vector<std::shared_ptr<IPrimitive>> primitives(matrixs.size());
	for (int i = 0; i < matrixs.size(); i++)
	{
		auto primitive = pPrimitive[0]->Clone();
		primitive->Multi(matrixs[i]);
		primitives[i] = primitive;
	}

	m_pRenderItem[0] = std::make_unique<MultiRenderItem>(primitives);

}
void MultiDrawElementsDrawer::Draw(const mat4x4& proj, const mat4x4& view)
{
	glEnableVertexAttribArray(ATTRIB_POSITION);
	glEnableVertexAttribArray(ATTRIB_NORMAL);

	m_pShader->Use();
	m_pShader->SetViewProj(proj*view);
	m_pShader->SetModel(mat4x4(1));
	for (int i = 0; i < m_pRenderItem.size(); i++)
	{
		auto pItem = (MultiRenderItem*)m_pRenderItem[i].get();

		pItem->PositionBuffer()->Bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		pItem->NormalBuffer()->Bind();
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		pItem->IndexBuffer()->Bind();

		glMultiDrawElements(pItem->GetDrawType(),
			pItem->DrawCount().data(),
			GL_UNSIGNED_INT,
			pItem->DrawIndicies().data(),
			pItem->PrimitiveNum());

	}

}