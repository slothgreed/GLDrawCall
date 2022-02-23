#ifndef RENDER_ITEM_H
#define RENDER_ITEM_H
#include "IRenderItem.h"
class RenderItem : public IRenderItem
{
public:
	RenderItem(const std::shared_ptr<IPrimitive>& pPrimitive);
	~RenderItem();

	GLint GetDrawType();
private:
	void BuildGLBuffer();
	mat4x4 m_matrix;

	std::shared_ptr<IPrimitive> m_pPrimitive;
};


#endif