#ifndef MULTI_RENDER_ITEM_H
#define MULTI_RENDER_ITEM_H

#include "IRenderItem.h"
class MultiRenderItem : public IRenderItem
{
public:
	MultiRenderItem(std::vector<std::shared_ptr<IPrimitive>>& pPrimitives);
	~MultiRenderItem();

	GLint GetDrawType();
	bool IsInterleave() { return m_isInterleave; }
	std::vector<void*>& DrawIndicies() { return m_drawIndices; }
	std::vector<int>& DrawCount() { return m_drawCount; }
	int PrimitiveNum() { return m_primitiveNum; }
private:
	void BuildGLBuffer(std::vector<std::shared_ptr<IPrimitive>>& pPrimitives);


	std::shared_ptr<IPrimitive> m_pPrimitive;

	std::vector<void*> m_drawIndices;
	std::vector<int> m_drawCount;

	GLint m_drawType;
	int m_primitiveNum;
	bool m_isInterleave;

};

#endif 