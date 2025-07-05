#pragma once
#include "Renderer.h"

class VertexBuffer {
private:
	unsigned int m_Renderer_ID;//ID used on a lower level closer to Open GL. To refer directly to the ID of the current command
	unsigned int vb;
public:
	VertexBuffer();
	~VertexBuffer();
	void VertexBufferAssign(const void* data, unsigned int size);

	void Bind() const;
	void UnBind() const;

};