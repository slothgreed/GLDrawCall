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
	GLuint PrimitiveType() { return m_drawType; }

protected:
	std::unique_ptr<GLBuffer> m_pPositionBuffer;
	std::unique_ptr<GLBuffer> m_pNormalBuffer;

	std::unique_ptr<GLBuffer> m_pIndexBuffer;
	GLuint m_drawType;
};

#endif