#ifndef BEGINEND_DRAWER_H
#define BEGINEND_DRAWER_H
#include "IDrawer.h"

class BeginEndDrawer : public IDrawer
{
public:
	BeginEndDrawer();
	~BeginEndDrawer();

	virtual void BuildRenderItem(const Primitives& pPrimitive, std::vector<mat4x4>&& matrixs) override;
	virtual void Draw(const mat4x4& proj, const mat4x4& view) override;

private:
	Primitives m_pPrimitives;
	std::vector<mat4x4> m_matrix;

};


#endif BEGINEND_DRAWER_H