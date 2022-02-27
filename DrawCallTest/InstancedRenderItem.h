#ifndef INSTANCED_RENDER_ITEM_H
#define INSTANCED_RENDER_ITEM_H
#include "RenderItem.h"
class InstancedRenderItem : public RenderItem
{
public:
	InstancedRenderItem(const std::shared_ptr<IPrimitive>& pPrimitive, const std::vector<glm::mat4x4>& matrix);
	~InstancedRenderItem();

	std::unique_ptr<GLBuffer>& MatrixBuffer() { return m_pMatrixBuffer; }
	std::unique_ptr<GLBuffer>& MatrixIndexBuffer() { return m_pMatrixIndexBuffer; }
	int ItemNum() { return m_itemNum; }
protected:
	virtual void BuildGLBuffer(const std::vector<glm::mat4x4>& matrix);
private:
	int m_itemNum;
	std::unique_ptr<GLBuffer> m_pMatrixBuffer;
	std::unique_ptr<GLBuffer> m_pMatrixIndexBuffer;
};


#endif INSTANCED_RENDER_ITEM_H