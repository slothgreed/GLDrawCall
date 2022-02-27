#include "DrawElementsIndirectDrawer.h"
#include "MultiRenderItem.h"
#include "InstanceShader.h"
DrawElementsIndirectDrawer::DrawElementsIndirectDrawer()
	:IDrawer(std::make_unique<InstanceShader>())
{
}

DrawElementsIndirectDrawer::~DrawElementsIndirectDrawer()
{
}

void DrawElementsIndirectDrawer::BuildRenderItem(const Primitives& pPrimitives, std::vector<mat4x4>&& matrixs)
{
	m_commands.resize(1);


	m_pRenderItem.push_back(std::make_unique<MultiRenderItem>(pPrimitives, true));

	std::vector<std::shared_ptr<IPrimitive>> pPrimitive;

	m_commands[0].vertexCount = pPrimitives[0]->Index().size();
	m_commands[0].instanceCount = matrixs.size();
	m_commands[0].firstIndex = 0;
	m_commands[0].baseVertex = 0;
	m_commands[0].baseInstance = 0;

	glCreateBuffers(1, &m_indirectBuffer);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_indirectBuffer);
	glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(DrawElementsIndirectCommand) * m_commands.size(), m_commands.data(), GL_DYNAMIC_COPY);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
	OUTPUT_GLERROR;

	glEnableVertexAttribArray(ATTRIB_POSITION);
	glEnableVertexAttribArray(ATTRIB_NORMAL);
	glEnableVertexAttribArray(ATTRIB_MATRIX);
	OUTPUT_GLERROR;

	glVertexBindingDivisor(ATTRIB_POSITION, 0);
	glVertexBindingDivisor(ATTRIB_NORMAL, 0);
	glVertexBindingDivisor(ATTRIB_MATRIX, 1);
	OUTPUT_GLERROR;

	glVertexAttribFormat(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribFormat(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, m_normal));
	glVertexAttribIFormat(ATTRIB_MATRIX, 1, GL_INT, 0);
	OUTPUT_GLERROR;

	glBindVertexBuffer(ATTRIB_POSITION, m_pRenderItem[0]->PositionBuffer()->GetId(), 0, sizeof(glm::vec3));
	glBindVertexBuffer(ATTRIB_NORMAL, m_pRenderItem[0]->NormalBuffer()->GetId(), 0, sizeof(glm::vec3));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pRenderItem[0]->IndexBuffer()->GetId());

	//m_pShader->SetModelBuffer(((MultiRenderItem*)m_pRenderItem[0].get())->ma);
	m_pShader->Use();
	OUTPUT_GLERROR;
}

void DrawElementsIndirectDrawer::Draw(const mat4x4& proj, const mat4x4& view)
{

	m_pShader->SetViewProj(proj*view);

	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_indirectBuffer);
	glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
	OUTPUT_GLERROR;
}