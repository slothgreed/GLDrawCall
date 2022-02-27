#ifndef INSTANCE_SHADER_H
#define INSTANCE_SHADER_H

#include "IShader.h"
#include "GLBuffer.h"
#include "MatrixTexture.h"
class InstanceShader : public IShader
{
public:


	InstanceShader();
	~InstanceShader();

	virtual std::string GetVertexPath() override;
	virtual std::string GetFragmentPath() override;

	virtual void GetUniformLocation() override;
	virtual void SetViewProj(const mat4x4& value) override;
	virtual void SetModelBuffer(std::unique_ptr<GLBuffer>& buffer) override;
private:
	enum UNIFORM
	{
		VIEW_PROJ,
		NUM
	};

	GLuint m_uniform[UNIFORM::NUM];
	std::unique_ptr<MatrixTexture> m_pMatrixTexture;
};

#endif INSTANCE_SHADER_H