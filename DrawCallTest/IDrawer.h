#ifndef IDRAER_H
#define IDRAER_H

#include "IRenderItem.h"
#include "IShader.h"

typedef std::vector<std::shared_ptr<IPrimitive>> Primitives;
class IDrawer
{
public:
	IDrawer() {};
	virtual ~IDrawer() {};

	virtual void BuildRenderItem(const Primitives& pPrimitive, std::vector<mat4x4>&& matrixs) = 0;
	virtual void Draw(const mat4x4& proj, const mat4x4& view) = 0;

protected:

};

#endif IDRAER_H