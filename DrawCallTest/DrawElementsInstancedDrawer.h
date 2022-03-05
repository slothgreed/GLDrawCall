#ifndef DRAW_ELEMENTS_INSTANCED_DRAWER_H
#define DRAW_ELEMENTS_INSTANCED_DRAWER_H
#include "IDrawer.h"
#include "InstanceShader.h"
#include "RenderItem.h"
#include <vector>
class DrawElementsInstancedDrawer : public IDrawer
{
public:
	DrawElementsInstancedDrawer();
	~DrawElementsInstancedDrawer();

	virtual void BuildRenderItem(const Primitives& pPrimitive, std::vector<mat4x4>&& matrixs) override;
	virtual void Draw(const mat4x4& proj, const mat4x4& view) override;

private:
	std::unique_ptr<InstanceShader> m_pShader;
	std::vector<std::unique_ptr<RenderItem>> m_pRenderItem;

	int m_objectNum;
};


#endif DRAW_ELEMENTS_INSTANCED_DRAWER_H