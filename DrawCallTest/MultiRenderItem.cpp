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

	std::vector<glm::vec3> position;
	m_pPositionBuffer = std::make_unique<GLBuffer>(GL_ARRAY_BUFFER);

	std::vector<glm::vec3> normal;
	m_pNormalBuffer = std::make_unique<GLBuffer>(GL_ARRAY_BUFFER);


	for (int i = 0; i < pPrimitives.size(); i++)
	{
		position.insert(position.end(), pPrimitives[i]->Position().begin(),pPrimitives[i]->Position().end());
		normal.insert(normal.end(), pPrimitives[i]->Normal().begin(), pPrimitives[i]->Normal().end());
	}

	m_pPositionBuffer->Build(position);
	m_pNormalBuffer->Build(normal);

	int index = 0;
	std::vector<int> indexArray;
	int indexSum = 0;
	if (m_useBaseVertex)
	{
		for (int i = 0; i < pPrimitives.size(); i++)
		{
			indexArray.insert(indexArray.end(), pPrimitives[i]->Index().begin(), pPrimitives[i]->Index().end());
			m_baseVertex.push_back(indexSum);
			indexSum += pPrimitives[i]->Position().size();
		}

	}
	else
	{
		int indexSum = 0;
		for (int i = 0; i < pPrimitives.size(); i++)
		{
			for (int j = 0; j < pPrimitives[i]->Index().size(); j++)
			{
				indexArray.push_back(pPrimitives[i]->Index()[j] + indexSum);
			}
			indexSum += pPrimitives[i]->Position().size();
		}
	}

	m_drawIndices.resize(pPrimitives.size());
	m_drawCount.resize(pPrimitives.size());

	int offset = 0;
	for (int i = 0; i < pPrimitives.size(); i++)
	{
		m_drawIndices[i] = (void*)(offset * sizeof(unsigned int));
		m_drawCount[i] =  pPrimitives[i]->Index().size();
		offset += pPrimitives[i]->Index().size();
	}

	m_pIndexBuffer = std::make_unique<GLBuffer>(GL_ELEMENT_ARRAY_BUFFER);
	m_pIndexBuffer->Build(indexArray);
}

