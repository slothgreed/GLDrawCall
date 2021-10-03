#include "DrawElementsIndirectDrawer.h"
#include "RenderItem.h"
#include "InstanceShader.h"
DrawElementsIndirectDrawer::DrawElementsIndirectDrawer()
	:IDrawer(std::make_unique<InstanceShader>())
{
}

DrawElementsIndirectDrawer::~DrawElementsIndirectDrawer()
{
}

void DrawElementsIndirectDrawer::BuildRenderItem(std::shared_ptr<IPrimitive> pPrimitive, int range)
{
}

void DrawElementsIndirectDrawer::Draw(const mat4x4& proj, const mat4x4& view)
{

}