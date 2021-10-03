#ifndef GL_BUFFER_H
#define GL_BUFFER_H
#include "IPrimitive.h"
enum class BUFFER_TYPE
{
	ARRAY,
	ELEMENT_ARRAY
};

class GLBuffer
{
public:
	GLBuffer(GLenum type);
	~GLBuffer();


	bool Created() { return m_id != 0; }
	void Bind();
	void UnBind();
	void Delete();
	void Build(const std::vector<glm::vec3>& value);
	void Build(const std::vector<int>& value);
	void Build(const std::vector<Vertex>& value);

	void NamedBufferData(const std::vector<mat4x4>& value);
	void NamedBufferData(const std::vector<int>& value);

	GLuint GetId() { return m_id; }
	int Size();
private:
	int m_size;
	GLenum m_type;
	GLuint m_id;
};


#endif GL_BUFFER_H