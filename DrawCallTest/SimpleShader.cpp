#include "SimpleShader.h"
#include "ShaderUtility.h"

using namespace std;
SimpleShader::SimpleShader()
{
}

SimpleShader::~SimpleShader()
{
	Delete();
}

std::string SimpleShader::GetVertexPath()
{
	return  ".\\Shader\\simple.vert";
}
std::string SimpleShader::GetFragmentPath()
{
	return ".\\Shader\\simple.frag";
}
void SimpleShader::GetUniformLocation()
{
	m_uniform[UNIFORM::VIEW_PROJ] = glGetUniformLocation(GetId(), "u_VP");
	m_uniform[UNIFORM::MODEL] = glGetUniformLocation(GetId(), "u_Model");
}

void SimpleShader::SetViewProj(const mat4x4& value)
{
	glUniformMatrix4fv(m_uniform[UNIFORM::VIEW_PROJ], 1, GL_FALSE, &value[0][0]);
}

void SimpleShader::SetModel(const mat4x4& value)
{
	glUniformMatrix4fv(m_uniform[UNIFORM::MODEL], 1, GL_FALSE, &value[0][0]);
}

