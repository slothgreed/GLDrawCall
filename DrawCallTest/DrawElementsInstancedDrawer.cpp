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
	m_pShader->SetModels(matrixs);
	OUTPUT_GLERROR;
	m_pRenderItem.push_back(std::make_unique<RenderItem>(pPrimitives[0]));
	m_objectNum = matrixs.size();

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
	auto pItem = (RenderItem*)m_pRenderItem[0].get();
	glBindVertexBuffer(ATTRIB_POSITION, pItem->PositionBuffer()->GetId(), 0, sizeof(glm::vec3));
	glBindVertexBuffer(ATTRIB_NORMAL, pItem->NormalBuffer()->GetId(), 0, sizeof(glm::vec3));
	OUTPUT_GLERROR;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pItem->IndexBuffer()->GetId());
	glDrawElementsInstanced(pItem->GetDrawType(), pItem->IndexBuffer()->Size(), GL_UNSIGNED_INT, 0, m_objectNum);
	OUTPUT_GLERROR;
}