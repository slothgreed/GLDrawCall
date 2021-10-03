#include "InstanceShader.h"

InstanceShader::InstanceShader()
{
	m_pMatrixBuffer = std::make_unique<GLBuffer>(0);
	m_pMatrixIndexBuffer = std::make_unique<GLBuffer>(0);
	m_pMatrixTexture = std::make_unique<MatrixTexture>();
}

InstanceShader::~InstanceShader()
{
}

std::string InstanceShader::GetVertexPath()
{
	return  "E:\\MyProgram\\KIProject\\DrawCallTest\\DrawCallTest\\Shader\\instance.vert";
}
std::string InstanceShader::GetFragmentPath()
{
	return "E:\\MyProgram\\KIProject\\DrawCallTest\\DrawCallTest\\Shader\\instance.frag";
}
void InstanceShader::GetUniformLocation()
{
	m_uniform[UNIFORM::VIEW_PROJ] = glGetUniformLocation(GetId(), "u_VP");
}

void InstanceShader::SetViewProj(const mat4x4& value)
{
	glUniformMatrix4fv(m_uniform[UNIFORM::VIEW_PROJ], 1, GL_FALSE, &value[0][0]);
}

void InstanceShader::SetModels(const std::vector<mat4x4>& value)
{
	IShader::Use();
	m_pMatrixBuffer->NamedBufferData(value);
	m_pMatrixTexture->TextureBuffer(m_pMatrixBuffer->GetId());

	std::vector<int> index(value.size());
	for (int i = 0; i < value.size(); i++) {
		index[i] = i;
	}
	m_pMatrixIndexBuffer->NamedBufferData(index);

}

void InstanceShader::Use()
{
	IShader::Use();
	glActiveTexture(GL_TEXTURE0);
	m_pMatrixTexture->Bind();
	glBindVertexBuffer(ATTRIB_MATRIX, m_pMatrixIndexBuffer->GetId(), 0, sizeof(int));

	//m_pMatrixBuffer->Bind();
	//m_pMatrixIndexBuffer->Bind();

}
