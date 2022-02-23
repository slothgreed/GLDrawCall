#ifndef DRAW_ELEMENT_DRAWER_H
#define DRAW_ELEMENT_DRAWER_H

#include "IDrawer.h"
class DrawElementsDrawer : public IDrawer
{
public:
	DrawElementsDrawer();
	~DrawElementsDrawer();

	virtual void BuildRenderItem(const Primitives& pPrimitive, std::vector<mat4x4>&& matrixs) override;
	virtual void Draw(const mat4x4& proj, const mat4x4& view) override;

private:
	std::vector<mat4x4> m_matrixs;
};



#endif DRAW_ELEMENT_DRAWER_H