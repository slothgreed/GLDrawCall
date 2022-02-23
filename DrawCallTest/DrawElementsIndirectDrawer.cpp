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

void DrawElementsIndirectDrawer::BuildRenderItem(std::shared_ptr<IPrimitive> pPrimitive, int range)
{
	m_pRenderItem.resize(1);
	m_commands.resize(range * range * range);

	std::vector<mat4> matrices(range * range * range);
	std::vector<std::shared_ptr<IPrimitive>> pPrimitives(1);

	int baseVertex = 0;
	for (int x = 0; x < range; x++)
	{
		for (int y = 0; y < range; y++)
		{
			for (int z = 0; z < range; z++)
			{
				int index = x * range * range + y * range + z;
				matrices[index] = glm::translate(mat4x4(1), vec3(x, y, z));
			}
		}
	}

	m_commands[0].vertexCount = pPrimitive->Index().size();
	m_commands[0].instanceCount = matrices.size();
	m_commands[0].firstIndex = 0;
	m_commands[0].baseVertex = 0;
	m_commands[0].baseInstance = 0;

	pPrimitives[0] = pPrimitive;
	m_pRenderItem[0] = std::make_unique<MultiRenderItem>(pPrimitives);

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
	m_pRenderItem[0]->IndexBuffer()->Bind();

	m_pShader->SetModels(matrices);
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