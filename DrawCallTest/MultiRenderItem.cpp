#include "MultiRenderItem.h"

MultiRenderItem::MultiRenderItem(const Primitives& pPrimitives, bool useBaseVertex)
	:m_useBaseVertex(useBaseVertex)
{
	BuildGLBuffer(pPrimitives);
}

MultiRenderItem::~MultiRenderItem()
{
}

void MultiRenderItem::BuildGLBuffer(const Primitives& pPrimitives)
{
	assert(pPrimitives.size() != 0);
	assert(pPrimitives[0]->Index().size() != 0);
	m_primitiveNum = pPrimitives.size();

	{
		
		int positionNum = 0;
		for (int i = 0; i < pPrimitives.size(); i++)
		{
			positionNum += pPrimitives[i]->Position().size();
		}

		m_pPositionBuffer = std::make_unique<GLBuffer>(GL_ARRAY_BUFFER);
		m_pNormalBuffer = std::make_unique<GLBuffer>(GL_ARRAY_BUFFER);
		m_pPositionBuffer->Create(positionNum, sizeof(glm::vec3));
		m_pNormalBuffer->Create(positionNum, sizeof(glm::vec3));

		int offset = 0;
		for (int i = 0; i < pPrimitives.size(); i++)
		{
			m_pPositionBuffer->BufferSubData(offset, pPrimitives[i]->Position());
			m_pNormalBuffer->BufferSubData(offset, pPrimitives[i]->Normal());
			offset += pPrimitives[i]->Position().size();
		}
	}

	int index = 0;
	int indexSum = 0;
	if (m_useBaseVertex)
	{
		m_pIndexBuffer = std::make_unique<GLBuffer>(GL_ELEMENT_ARRAY_BUFFER);

		int indexNum = 0;
		for (int i = 0; i < pPrimitives.size(); i++)
		{
			indexNum += pPrimitives[i]->Index().size();
		}

		m_pIndexBuffer->Create(indexNum, sizeof(int));
		int offset = 0;
		for (int i = 0; i < pPrimitives.size(); i++)
		{
			m_pIndexBuffer->BufferSubData(offset, pPrimitives[i]->Index());
			offset += pPrimitives[i]->Index().size();
			
			m_baseVertex.push_back(indexSum);
			indexSum += pPrimitives[i]->Position().size();
		}
	}
	else
	{
		std::vector<int> indexArray;
		int indexSum = 0;
		for (int i = 0; i < pPrimitives.size(); i++)
		{
			for (int j = 0; j < pPrimitives[i]->Index().size(); j++)
			{
				indexArray.push_back(pPrimitives[i]->Index()[j] + indexSum);
			}
			indexSum += pPrimitives[i]->Position().size();
		}

		m_pIndexBuffer = std::make_unique<GLBuffer>(GL_ELEMENT_ARRAY_BUFFER);
		m_pIndexBuffer->Create(indexArray);
	}


	m_drawIndices.resize(pPrimitives.size());
	m_drawCount.resize(pPrimitives.size());

	{

		int offset = 0;
		for (int i = 0; i < pPrimitives.size(); i++)
		{
			m_drawIndices[i] = (void*)(offset * sizeof(unsigned int));
			m_drawCount[i] = pPrimitives[i]->Index().size();
			offset += pPrimitives[i]->Index().size();
		}
	}

}

