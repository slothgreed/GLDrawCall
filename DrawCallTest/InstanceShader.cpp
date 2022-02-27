#include "InstanceShader.h"

InstanceShader::InstanceShader()
{
	m_pMatrixTexture = std::make_unique<MatrixTexture>();
}

InstanceShader::~InstanceShader()
{
}

std::string InstanceShader::GetVertexPath()
{
	return  "E:\\MyProgram\\KIProject\\GLDrawCall\\DrawCallTest\\Shader\\instance.vert";
}
std::string InstanceShader::GetFragmentPath()
{
	return "E:\\MyProgram\\KIProject\\GLDrawCall\\DrawCallTest\\Shader\\instance.frag";
}
void InstanceShader::GetUniformLocation()
{
	m_uniform[UNIFORM::VIEW_PROJ] = glGetUniformLocation(GetId(), "u_VP");
}

void InstanceShader::SetViewProj(const mat4x4& value)
{
	glUniformMatrix4fv(m_uniform[UNIFORM::VIEW_PROJ], 1, GL_FALSE, &value[0][0]);
}

void InstanceShader::SetModelBuffer(std::unique_ptr<GLBuffer>& buffer)
{
	//need use shader
	m_pMatrixTexture->TextureBuffer(buffer->GetId());
	glActiveTexture(GL_TEXTURE0);
	m_pMatrixTexture->Bind();
}
