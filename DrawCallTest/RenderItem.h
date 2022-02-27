#ifndef RENDER_ITEM_H
#define RENDER_ITEM_H
#include "IRenderItem.h"
class RenderItem : public IRenderItem
{
public:
	RenderItem(const std::shared_ptr<IPrimitive>& pPrimitive);
	~RenderItem();

	std::unique_ptr<GLBuffer>& MatrixBuffer() { return m_pMatrixBuffer; }
	std::unique_ptr<GLBuffer>& MatrixIndexBuffer() { return m_pMatrixIndexBuffer; }
	
	int ItemNum() { return m_itemNum; }
	void SetModels(const std::vector<glm::mat4x4>& matrix);
protected :
		virtual void BuildGLBuffer();
private:
	std::shared_ptr<IPrimitive> m_pPrimitive;

	int m_itemNum;
	std::unique_ptr<GLBuffer> m_pMatrixBuffer;
	std::unique_ptr<GLBuffer> m_pMatrixIndexBuffer;
};


#endif