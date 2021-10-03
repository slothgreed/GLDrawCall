#ifndef DRAW_ELEMENTS_INSTANCED_DRAWER_H
#define DRAW_ELEMENTS_INSTANCED_DRAWER_H
#include "IDrawer.h"
class DrawElementsInstancedDrawer : public IDrawer
{
public:
	DrawElementsInstancedDrawer();
	~DrawElementsInstancedDrawer();

	virtual void BuildRenderItem(std::shared_ptr<IPrimitive> pPrimitive, int range) override;
	virtual void Draw(const mat4x4& proj, const mat4x4& view) override;

private:
	int m_objectNum;
};


#endif DRAW_ELEMENTS_INSTANCED_DRAWER_H