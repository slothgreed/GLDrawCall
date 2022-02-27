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

void MultiDrawElementsDrawer::BuildRenderItem(const Primitives& pPrimitives, std::vector<mat4x4>&& matrixs)
{
	int num = 0;
	while (num < matrixs.size())
	{
		std::vector<std::shared_ptr<IPrimitive>> primitives(pPrimitives.size());
		for (int j = 0; j < pPrimitives.size(); j++)
		{
			auto primitive = pPrimitives[j]->Clone();
			primitive->Multi(matrixs[num++]);
			primitives[j] = primitive;
		}
		m_pRenderItem.push_back(std::make_unique<MultiRenderItem>(primitives, false));
	}

	m_pShader->Use();
	m_pShader->SetModel(mat4x4(1));
	glEnableVertexAttribArray(ATTRIB_POSITION);
	glEnableVertexAttribArray(ATTRIB_NORMAL);
	glVertexAttribFormat(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribFormat(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, 0);
	OUTPUT_GLERROR;
}
void MultiDrawElementsDrawer::Draw(const mat4x4& proj, const mat4x4& view)
{
	m_pShader->SetViewProj(proj*view);
	for (int i = 0; i < m_pRenderItem.size(); i++)
	{
		auto pItem = (MultiRenderItem*)m_pRenderItem[i].get();
		glBindVertexBuffer(ATTRIB_POSITION, pItem->PositionBuffer()->GetId(), 0, sizeof(glm::vec3));
		glBindVertexBuffer(ATTRIB_NORMAL, pItem->NormalBuffer()->GetId(), 0, sizeof(glm::vec3));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pItem->IndexBuffer()->GetId());
		if (pItem->UseBaseVertex())
		{
			glMultiDrawElementsBaseVertex(GL_TRIANGLES,
				pItem->DrawCount().data(),
				GL_UNSIGNED_INT,
				pItem->DrawIndicies().data(),
				pItem->PrimitiveNum(),
				pItem->BaseVertex().data());
		}
		else
		{
			glMultiDrawElements(GL_TRIANGLES,
				pItem->DrawCount().data(),
				GL_UNSIGNED_INT,
				pItem->DrawIndicies().data(),
				pItem->PrimitiveNum());

		}
		OUTPUT_GLERROR;
	}

}