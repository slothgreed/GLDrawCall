#ifndef IDRAER_H
#define IDRAER_H

#include "IRenderItem.h"
#include "IShader.h"

class IDrawer
{
public:
	IDrawer(std::unique_ptr<IShader>&& pShader);
	virtual ~IDrawer() {};

	virtual void BuildRenderItem(std::shared_ptr<IPrimitive> pPrimitive, int range) = 0;
	virtual void Draw(const mat4x4& proj, const mat4x4& view) = 0;

protected:
	std::unique_ptr<IShader> m_pShader;
	std::vector<std::unique_ptr<IRenderItem>> m_pRenderItem;

};

#endif IDRAER_H