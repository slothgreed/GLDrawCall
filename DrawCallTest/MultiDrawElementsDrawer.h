#ifndef MULTI_DRAW_ARRAY_DRAWER_H
#define MULTI_DRAW_ARRAY_DRAWER_H
#include "MultiRenderItem.h"
#include "SimpleShader.h"
#include "IDrawer.h"
class MultiDrawElementsDrawer : public IDrawer
{
public:
	MultiDrawElementsDrawer(bool useBaseVertex);
	~MultiDrawElementsDrawer();

	virtual void BuildRenderItem(const Primitives& pPrimitive, std::vector<mat4x4>&& matrixs) override;
	virtual void Draw(const mat4x4& proj, const mat4x4& view) override;

private:
	bool m_useBaseVertex;
	std::unique_ptr<SimpleShader> m_pShader;
	std::vector<std::unique_ptr<MultiRenderItem>> m_pRenderItem;

};


#endif MULTI_DRAW_ARRAY_DRAWER_H