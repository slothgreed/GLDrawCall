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

void DrawElementsInstancedDrawer::BuildRenderItem(const Primitives& pPrimitives, std::vector<mat4x4>&& matrixs)
{
	std::vector<std::vector<glm::mat4x4>> primitiveMatrix(pPrimitives.size());
	int num = 0;
	while (num < matrixs.size())
	{
		for (int i = 0; i < pPrimitives.size(); i++)
		{
			primitiveMatrix[i].push_back(matrixs[num++]);
		}
	}

	OUTPUT_GLERROR;

	for (int i = 0; i < pPrimitives.size(); i++)
	{
		m_pRenderItem.push_back(std::make_unique<InstancedRenderItem>(pPrimitives[i], primitiveMatrix[i]));
	}


	m_pShader->Use();
	glEnableVertexAttribArray(ATTRIB_POSITION);
	glEnableVertexAttribArray(ATTRIB_NORMAL);
	glEnableVertexAttribArray(ATTRIB_MATRIX);
	OUTPUT_GLERROR;

	glVertexBindingDivisor(ATTRIB_POSITION, 0);
	glVertexBindingDivisor(ATTRIB_NORMAL, 0);
	glVertexBindingDivisor(ATTRIB_MATRIX, 1);
	OUTPUT_GLERROR;


	glVertexAttribFormat(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribFormat(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribIFormat(ATTRIB_MATRIX, 1, GL_INT, 0);
}

void DrawElementsInstancedDrawer::Draw(const mat4x4& proj, const mat4x4& view)
{

	m_pShader->SetViewProj(proj*view);
	for (int i = 0; i < m_pRenderItem.size(); i++)
	{
		auto pItem = (InstancedRenderItem*)m_pRenderItem[i].get();
		m_pShader->SetModelBuffer(pItem->MatrixBuffer());
		glBindVertexBuffer(ATTRIB_POSITION, pItem->PositionBuffer()->GetId(), 0, sizeof(glm::vec3));
		glBindVertexBuffer(ATTRIB_NORMAL, pItem->NormalBuffer()->GetId(), 0, sizeof(glm::vec3));
		glBindVertexBuffer(ATTRIB_MATRIX, pItem->MatrixIndexBuffer()->GetId(), 0, sizeof(int));
		OUTPUT_GLERROR;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pItem->IndexBuffer()->GetId());
		glDrawElementsInstanced(GL_TRIANGLES, pItem->IndexBuffer()->Size(), GL_UNSIGNED_INT, 0, pItem->ItemNum());
		OUTPUT_GLERROR;
	}
}