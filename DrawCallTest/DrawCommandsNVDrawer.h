#ifndef DRAW_COMMANDS_NV_H
#define DRAW_COMMANDS_NV_H

#include "IDrawer.h"

class DrawCommandsNVDrawer : public IDrawer
{
public:
	DrawCommandsNVDrawer();
	~DrawCommandsNVDrawer();

	virtual void BuildRenderItem(const Primitives& pPrimitive, std::vector<mat4x4>&& matrixs) override;
	virtual void Draw(const mat4x4& proj, const mat4x4& view) override;

private:
	Primitives m_pPrimitives;
	std::vector<mat4x4> m_matrix;
};



#endif DRAW_COMMANDS_NV_H