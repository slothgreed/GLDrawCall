#include "InstancedRenderItem.h"
InstancedRenderItem::InstancedRenderItem(const std::shared_ptr<IPrimitive>& pPrimitive, const std::vector<glm::mat4x4>& matrix)
	: RenderItem(pPrimitive)
{
	m_pMatrixIndexBuffer = std::make_unique<GLBuffer>(0);
	m_pMatrixBuffer = std::make_unique<GLBuffer>(0);
	BuildGLBuffer(matrix);
}

InstancedRenderItem::~InstancedRenderItem()
{
}

void InstancedRenderItem::BuildGLBuffer(const std::vector<glm::mat4x4>& matrix)
{
	RenderItem::BuildGLBuffer();

	m_pMatrixBuffer->NamedBufferData(matrix);
	std::vector<int> index(matrix.size());
	for (int i = 0; i < index.size(); i++) {
		index[i] = i;
	}
	m_pMatrixIndexBuffer->NamedBufferData(index);
	m_itemNum = matrix.size();

}