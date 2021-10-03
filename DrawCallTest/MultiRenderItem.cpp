#include "MultiRenderItem.h"

MultiRenderItem::MultiRenderItem(std::vector<std::shared_ptr<IPrimitive>>& pPrimitives)
	:m_isInterleave(false)
{
	BuildGLBuffer(pPrimitives);
}

MultiRenderItem::~MultiRenderItem()
{
}

void MultiRenderItem::BuildGLBuffer(std::vector<std::shared_ptr<IPrimitive>>& pPrimitives)
{
	assert(pPrimitives.size() != 0);
	assert(pPrimitives[0]->Index().size() != 0);
	m_primitiveNum = pPrimitives.size();


	if (pPrimitives[0]->IsInterleave())
	{
		int arraySize = pPrimitives[0]->GetVertex().size() * pPrimitives.size();
		std::vector<Vertex> vertex(arraySize);
		m_pVertexBuffer = std::make_unique<GLBuffer>(GL_ARRAY_BUFFER);

		for (int i = 0; i < pPrimitives.size(); i++)
		{
			for (int j = 0; j < pPrimitives[i]->GetVertex().size(); j++)
			{
				int index = i * pPrimitives[i]->GetVertex().size() + j;
				vertex[index] = pPrimitives[i]->GetVertex()[j];
			}
		}

		m_pVertexBuffer->Build(vertex);
	}
	else
	{
		int arraySize = pPrimitives[0]->Position().size() * pPrimitives.size();
		std::vector<glm::vec3> position(arraySize);
		m_pPositionBuffer = std::make_unique<GLBuffer>(GL_ARRAY_BUFFER);

		std::vector<glm::vec3> normal(arraySize);
		m_pNormalBuffer = std::make_unique<GLBuffer>(GL_ARRAY_BUFFER);


		for (int i = 0; i < pPrimitives.size(); i++)
		{
			for (int j = 0; j < pPrimitives[i]->Position().size(); j++)
			{
				int index = i * pPrimitives[i]->Position().size() + j;
				position[index] = pPrimitives[i]->Position()[j];
				normal[index] = pPrimitives[i]->Normal()[j];
			}
		}

		m_pPositionBuffer->Build(position);
		m_pNormalBuffer->Build(normal);
	}


	int indexSize = pPrimitives[0]->Index().size() * pPrimitives.size();
	std::vector<int> indexArray(indexSize);
	for (int i = 0; i < pPrimitives.size(); i++)
	{
		for (int j = 0; j < pPrimitives[i]->Index().size(); j++)
		{
			int index = i * pPrimitives[i]->Index().size() + j;
			if (pPrimitives[0]->IsInterleave())
			{
				indexArray[index] = pPrimitives[i]->Index()[j] + pPrimitives[i]->GetVertex().size() * i;
			}
			else
			{
				indexArray[index] = pPrimitives[i]->Index()[j] + pPrimitives[i]->Position().size() * i;
			}
		}
	}

	m_drawIndices.resize(pPrimitives.size());
	m_drawCount.resize(pPrimitives.size());

	for (int i = 0; i < pPrimitives.size(); i++)
	{
		m_drawIndices[i] = (void*)(i * pPrimitives[i]->Index().size() * sizeof(unsigned int));
		m_drawCount[i] = pPrimitives[i]->Index().size();
	}


	m_pIndexBuffer = std::make_unique<GLBuffer>(GL_ELEMENT_ARRAY_BUFFER);
	m_pIndexBuffer->Build(indexArray);
	m_drawType = pPrimitives[0]->GetDrawType();
	m_isInterleave = pPrimitives[0]->GetStoreType() == IPrimitive::StoreType::Interleave;
}

GLint MultiRenderItem::GetDrawType()
{
	return m_drawType;
}