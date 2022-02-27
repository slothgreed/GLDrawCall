#ifndef RENDER_ITEM_H
#define RENDER_ITEM_H
#include "IRenderItem.h"
class RenderItem : public IRenderItem
{
public:
	RenderItem(const std::shared_ptr<IPrimitive>& pPrimitive);
	~RenderItem();

protected :
		virtual void BuildGLBuffer();
private:
	std::shared_ptr<IPrimitive> m_pPrimitive;
};


#endif