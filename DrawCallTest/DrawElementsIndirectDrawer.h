#ifndef DRAW_ELEMENT_INDIRECT_DRAWER_H
#define DRAW_ELEMENT_INDIRECT_DRAWER_H
#include "IDrawer.h"
#include "InstanceShader.h"
#include "MultiRenderItem.h"
struct DrawElementsIndirectCommand
{
	unsigned int count;
	unsigned int instanceCount;
	unsigned int firstIndex;
	unsigned int baseVertex;
	unsigned int baseInstance;
};

class DrawElementsIndirectDrawer : public IDrawer
{
public:
	DrawElementsIndirectDrawer();
	~DrawElementsIndirectDrawer();

	virtual void BuildRenderItem(const Primitives& pPrimitive, std::vector<mat4x4>&& matrixs) override;
	virtual void Draw(const mat4x4& proj, const mat4x4& view) override;

private:

	std::unique_ptr<InstanceShader> m_pShader;
	std::unique_ptr<MultiRenderItem> m_pRenderItem;
	GLuint m_indirectBuffer;
	std::vector<DrawElementsIndirectCommand> m_commands;
};


#endif DRAW_ELEMENT_INDIRECT_DRAWER_H