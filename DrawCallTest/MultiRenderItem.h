#ifndef MULTI_RENDER_ITEM_H
#define MULTI_RENDER_ITEM_H

#include "IRenderItem.h"
class MultiRenderItem : public IRenderItem
{
public:
	MultiRenderItem(const Primitives& pPrimitive);
	~MultiRenderItem();

	std::vector<void*>& DrawIndicies() { return m_drawIndices; }
	std::vector<int>& DrawCount() { return m_drawCount; }
	int PrimitiveNum() { return m_primitiveNum; }
private:
	void BuildGLBuffer(const Primitives& pPrimitive);


	std::shared_ptr<IPrimitive> m_pPrimitive;

	std::vector<void*> m_drawIndices;
	std::vector<int> m_drawCount;

	int m_primitiveNum;
	bool m_isInterleave;

};

#endif 