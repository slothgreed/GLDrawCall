#ifndef INSTANCE_SHADER_H
#define INSTANCE_SHADER_H

#include "IShader.h"
#include "GLBuffer.h"
#include "MatrixTexture.h"
class InstanceShader : public IShader
{
public:

	enum UNIFORM
	{
		VIEW_PROJ,
		NUM
	};

	InstanceShader();
	~InstanceShader();

	virtual std::string GetVertexPath() override;
	virtual std::string GetFragmentPath() override;

	virtual void GetUniformLocation() override;
	virtual void SetViewProj(const mat4x4& value) override;
	virtual void SetModels(const std::vector<mat4x4>& value) override;
	virtual void Use() override;
private:
	GLuint m_uniform[UNIFORM::NUM];
	std::unique_ptr<GLBuffer> m_pMatrixBuffer;
	std::unique_ptr<GLBuffer> m_pMatrixIndexBuffer;
	std::unique_ptr<MatrixTexture> m_pMatrixTexture;
};

#endif INSTANCE_SHADER_H