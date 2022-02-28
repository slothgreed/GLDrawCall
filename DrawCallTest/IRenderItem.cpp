#include "IRenderItem.h"

void IRenderItem::SetMatrixs(const std::vector<glm::mat4x4>& matrix)
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