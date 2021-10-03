#ifndef RENDER_ITEM_H
#define RENDER_ITEM_H
#include "IRenderItem.h"
class RenderItem : public IRenderItem
{
public:
	RenderItem(std::shared_ptr<IPrimitive> pPrimitive, const mat4x4& matrix);
	~RenderItem();

	void SetModelMatrix(const mat4x4& value) { m_matrix = value; }
	const mat4x4& ModelMatrix() { return m_matrix; }


	bool IsInterleave() { return m_pPrimitive->GetStoreType() == IPrimitive::StoreType::Interleave; }
	GLint GetDrawType();
private:
	void BuildGLBuffer();
	mat4x4 m_matrix;

	std::shared_ptr<IPrimitive> m_pPrimitive;
};


#endif