#ifndef MULTI_DRAW_ARRAY_DRAWER_H
#define MULTI_DRAW_ARRAY_DRAWER_H

#include "IDrawer.h"
class MultiDrawElementsDrawer : public IDrawer
{
public:
	MultiDrawElementsDrawer();
	~MultiDrawElementsDrawer();

	virtual void BuildRenderItem(std::shared_ptr<IPrimitive> pPrimitive, int range) override;
	virtual void Draw(const mat4x4& proj, const mat4x4& view) override;

private:
};


#endif MULTI_DRAW_ARRAY_DRAWER_H