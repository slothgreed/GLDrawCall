#include "RenderItem.h"

RenderItem::RenderItem(std::shared_ptr<IPrimitive> pPrimitive, const mat4x4& matrix)
	:m_pPrimitive(pPrimitive),
	m_matrix(matrix)
{
	BuildGLBuffer();
}


RenderItem::~RenderItem()
{
}

void RenderItem::BuildGLBuffer()
{
	if (m_pPrimitive->IsInterleave())
	{
		m_pVertexBuffer = std::make_unique<GLBuffer>(GL_ARRAY_BUFFER);
		m_pVertexBuffer->Build(m_pPrimitive->GetVertex());
	}
	else
	{
		assert(m_pPrimitive->Index().size() != 0);
		m_pPositionBuffer = std::make_unique<GLBuffer>(GL_ARRAY_BUFFER);
		m_pPositionBuffer->Build(m_pPrimitive->Position());

		m_pNormalBuffer = std::make_unique<GLBuffer>(GL_ARRAY_BUFFER);
		m_pNormalBuffer->Build(m_pPrimitive->Normal());
	}

	m_pIndexBuffer = std::make_unique<GLBuffer>(GL_ELEMENT_ARRAY_BUFFER);
	m_pIndexBuffer->Build(m_pPrimitive->Index());
}

GLint RenderItem::GetDrawType()
{
	return m_pPrimitive->GetDrawType();
}