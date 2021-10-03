#include "GLBuffer.h"
GLBuffer::GLBuffer(GLenum type)
	:m_type(type),
	m_id(0),
	m_size(0)
{
}

GLBuffer::~GLBuffer()
{
	Delete();
}

void GLBuffer::Build(const std::vector<glm::vec3>& value)
{
	assert(m_type != 0);
	Delete();
	glCreateBuffers(1, &m_id);
	glBindBuffer(m_type, m_id);
	glBufferData(m_type, value.size() * sizeof(glm::vec3), value.data(), GL_STATIC_DRAW);
	glBindBuffer(m_type, 0);
	m_size = value.size();
	OUTPUT_GLERROR;
}

void GLBuffer::Build(const std::vector<Vertex>& value)
{
	assert(m_type != 0);
	Delete();
	glCreateBuffers(1, &m_id);
	glBindBuffer(m_type, m_id);
	glBufferData(m_type, value.size() * sizeof(Vertex), value.data(), GL_STATIC_DRAW);
	glBindBuffer(m_type, 0);
	m_size = value.size();
	OUTPUT_GLERROR;
}

void GLBuffer::Build(const std::vector<int>& value)
{
	assert(m_type != 0);
	Delete();
	glCreateBuffers(1, &m_id);
	glBindBuffer(m_type, m_id);
	glBufferData(m_type, value.size() * sizeof(int), value.data(), GL_STATIC_DRAW);
	glBindBuffer(m_type, 0);
	m_size = value.size();
	OUTPUT_GLERROR;
}

void GLBuffer::NamedBufferData(const std::vector<mat4x4>& value)
{
	Delete();
	glCreateBuffers(1, &m_id);
	glNamedBufferData(m_id, sizeof(mat4x4) * value.size(), value.data(), GL_STATIC_DRAW);
	OUTPUT_GLERROR;
}

void GLBuffer::NamedBufferData(const std::vector<int>& value)
{
	Delete();
	glCreateBuffers(1, &m_id);
	glNamedBufferData(m_id, sizeof(int) * value.size(), value.data(), GL_STATIC_DRAW);
	OUTPUT_GLERROR;
}


void GLBuffer::Bind()
{
	assert(m_id != 0);
	glBindBuffer(m_type, m_id);
	OUTPUT_GLERROR;
}

void GLBuffer::UnBind()
{
	glBindBuffer(m_type, 0);
	OUTPUT_GLERROR;
}
void GLBuffer::Delete() 
{
	if (m_id != 0)
	{
		glDeleteBuffers(1, &m_id);
		OUTPUT_GLERROR;
		m_id = 0;
	}
}

int GLBuffer::Size()
{
	return m_size;
}