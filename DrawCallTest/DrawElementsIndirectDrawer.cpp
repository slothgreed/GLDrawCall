#include "DrawElementsIndirectDrawer.h"
#include "MultiRenderItem.h"
#include "InstanceShader.h"
DrawElementsIndirectDrawer::DrawElementsIndirectDrawer(bool multi)
	: m_pShader(std::make_unique<InstanceShader>())
	, m_multiDraw(multi)
{
	m_pShader->Build();
}

DrawElementsIndirectDrawer::~DrawElementsIndirectDrawer()
{
}

void DrawElementsIndirectDrawer::BuildRenderItem(const Primitives& pPrimitives, std::vector<mat4x4>&& matrixs)
{

	m_pRenderItem = std::make_unique<MultiRenderItem>(pPrimitives, true);
	m_pRenderItem->SetMatrixs(matrixs);

	std::vector<std::shared_ptr<IPrimitive>> pPrimitive;
	m_commands.resize(matrixs.size());
	int num = 0;
	while (num < matrixs.size())
	{
		for (int j = 0; j < pPrimitives.size(); j++)
		{
			m_commands[num].count = m_pRenderItem->IndexNum()[j];
			m_commands[num].instanceCount = 1;
			m_commands[num].firstIndex = m_pRenderItem->FirstIndex()[j];
			m_commands[num].baseVertex = m_pRenderItem->BaseVertex()[j];
			m_commands[num].baseInstance = num;
			num++;
		}
	}


	glCreateBuffers(1, &m_indirectBuffer);
	glNamedBufferData(m_indirectBuffer, sizeof(DrawElementsIndirectCommand) * m_commands.size(), m_commands.data(), GL_STATIC_DRAW);
	OUTPUT_GLERROR;

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
	OUTPUT_GLERROR;

	glBindVertexBuffer(ATTRIB_POSITION, m_pRenderItem->PositionBuffer()->GetId(), 0, sizeof(glm::vec3));
	glBindVertexBuffer(ATTRIB_NORMAL, m_pRenderItem->NormalBuffer()->GetId(), 0, sizeof(glm::vec3));
	glBindVertexBuffer(ATTRIB_MATRIX, m_pRenderItem->MatrixIndexBuffer()->GetId(), 0, sizeof(int));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pRenderItem->IndexBuffer()->GetId());

	m_pShader->SetModelBuffer(m_pRenderItem->MatrixBuffer());
	OUTPUT_GLERROR;
}

void DrawElementsIndirectDrawer::Draw(const mat4x4& proj, const mat4x4& view)
{

	m_pShader->SetViewProj(proj*view);

	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_indirectBuffer);

	if (m_multiDraw)
	{
		glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, 0, m_commands.size(), 0);
	}
	else
	{
		for (int i = 0; i < m_commands.size(); i++)
		{
			glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, (void*)(sizeof(DrawElementsIndirectCommand) * i));
		}
	}

	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
}