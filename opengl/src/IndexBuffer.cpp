#include "IndexBuffer.h"
//#include "Renderer.h"
#include "Logger.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	:m_Count(count)
{
	GLCall(glGenBuffers(1, &m_RendererID)); // create vertex buffer,
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); // bind buffer
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned) , data, GL_STATIC_DRAW)); //add data tu buffer
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));

}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); // bind buffer
}

void IndexBuffer::Unbind() const 
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // bind buffer
}