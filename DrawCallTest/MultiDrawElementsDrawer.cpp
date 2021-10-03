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

void MultiDrawElementsDrawer::BuildRenderItem(std::shared_ptr<IPrimitive> pPrimitive, int range)
{
	m_pRenderItem.resize(1);
	std::vector<std::shared_ptr<IPrimitive>> primitives(range*range*range);
	for (int x = 0; x < range; x++)
	{
		for (int y = 0; y < range; y++)
		{
			for (int z = 0; z < range; z++)
			{
				int index = x * range * range + y * range + z;
				mat4x4 matrix = glm::translate(mat4x4(1), vec3(x, y, z));
				auto primitive = pPrimitive->Clone();
				primitive->Multi(matrix);
				primitives[index] = primitive;

				//fprintf(stdout, "%d,%d,%d\n", x, y, z);
			}
		}
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

		if (pItem->IsInterleave())
		{
			pItem->VertexBuffer()->Bind();
			glVertexAttribPointer(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
			glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_normal));
		}
		else
		{
			pItem->PositionBuffer()->Bind();
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

			pItem->NormalBuffer()->Bind();
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		}

		pItem->IndexBuffer()->Bind();

		for (int i = 0; i < pItem->PrimitiveNum(); i++)
		{
			glDrawElements(pItem->GetDrawType(),
				pItem->DrawCount()[i],
				GL_UNSIGNED_INT,
				pItem->DrawIndicies()[i]);
		}

		//glMultiDrawElements(pItem->GetDrawType(),
		//	pItem->DrawCount().data(),
		//	GL_UNSIGNED_INT,
		//	pItem->DrawIndicies().data(),
		//	pItem->PrimitiveNum());

	}

}