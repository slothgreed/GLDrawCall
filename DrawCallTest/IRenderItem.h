#ifndef IRENDER_ITEM_H
#define IRENDER_ITEM_H
#include "IPrimitive.h"
#include "GLBuffer.h"
class IRenderItem
{
public:
	IRenderItem() {};
	virtual ~IRenderItem() {};

	std::unique_ptr<GLBuffer>& PositionBuffer() { return m_pPositionBuffer; }
	std::unique_ptr<GLBuffer>& NormalBuffer() { return m_pNormalBuffer; }

	std::unique_ptr<GLBuffer>& IndexBuffer() { return m_pIndexBuffer; }
	std::unique_ptr<GLBuffer>& MatrixBuffer() { return m_pMatrixBuffer; }
	std::unique_ptr<GLBuffer>& MatrixIndexBuffer() { return m_pMatrixIndexBuffer; }

	int ItemNum() { return m_itemNum; }
	void SetMatrixs(const std::vector<glm::mat4x4>& matrix);

protected:
	std::unique_ptr<GLBuffer> m_pPositionBuffer;
	std::unique_ptr<GLBuffer> m_pNormalBuffer;

	std::unique_ptr<GLBuffer> m_pIndexBuffer;

	int m_itemNum;
	std::unique_ptr<GLBuffer> m_pMatrixBuffer;
	std::unique_ptr<GLBuffer> m_pMatrixIndexBuffer;
};

#endif