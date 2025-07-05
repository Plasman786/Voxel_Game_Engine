#include "Renderer.h"

unsigned int m_Renderer_ID;
unsigned int vb;


VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &m_Renderer_ID);//make a vertex buffer object
}

//void VertexBufferAssign(const void* data, unsigned int size)
//{
//	glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_ID); // vertex buffer object binding
//	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);// vertex buffer object hints
//}
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_Renderer_ID);
}

void VertexBuffer::VertexBufferAssign(const void* data, unsigned int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_ID); // vertex buffer object binding
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);// vertex buffer object hints
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_ID);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
