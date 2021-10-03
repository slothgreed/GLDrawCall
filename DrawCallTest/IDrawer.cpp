#include "IDrawer.h"
IDrawer::IDrawer(std::unique_ptr<IShader>&& pShader) 
	:m_pShader(std::move(pShader))
{
	m_pShader->Build();
};
