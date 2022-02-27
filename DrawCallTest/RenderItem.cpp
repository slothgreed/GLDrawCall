#include "RenderItem.h"

RenderItem::RenderItem(const std::shared_ptr<IPrimitive>& pPrimitive)
	: m_pPrimitive(pPrimitive)
{
	BuildGLBuffer();
}


RenderItem::~RenderItem()
{
}

void RenderItem::BuildGLBuffer()
{
	assert(m_pPrimitive->Index().size() != 0);
	m_pPositionBuffer = std::make_unique<GLBuffer>(GL_ARRAY_BUFFER);
	m_pPositionBuffer->Create(m_pPrimitive->Position());

	m_pNormalBuffer = std::make_unique<GLBuffer>(GL_ARRAY_BUFFER);
	m_pNormalBuffer->Create(m_pPrimitive->Normal());

	m_pIndexBuffer = std::make_unique<GLBuffer>(GL_ELEMENT_ARRAY_BUFFER);
	m_pIndexBuffer->Create(m_pPrimitive->Index());

}

void RenderItem::SetModels(const std::vector<glm::mat4x4>& matrix)
{
	m_pMatrixBuffer = std::make_unique<GLBuffer>(0);
	m_pMatrixBuffer->Create(matrix);
	std::vector<int> index(matrix.size());
	for (int i = 0; i < index.size(); i++) {
		index[i] = i;
	}

	m_pMatrixIndexBuffer = std::make_unique<GLBuffer>(0);
	m_pMatrixIndexBuffer->Create(index);
	m_itemNum = matrix.size();
}