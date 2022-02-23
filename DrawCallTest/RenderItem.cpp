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
	m_pPositionBuffer->Build(m_pPrimitive->Position());

	m_pNormalBuffer = std::make_unique<GLBuffer>(GL_ARRAY_BUFFER);
	m_pNormalBuffer->Build(m_pPrimitive->Normal());

	m_pIndexBuffer = std::make_unique<GLBuffer>(GL_ELEMENT_ARRAY_BUFFER);
	m_pIndexBuffer->Build(m_pPrimitive->Index());

	m_drawType = m_pPrimitive->GetDrawType();
}

GLint RenderItem::GetDrawType()
{
	return m_pPrimitive->GetDrawType();
}