#pragma once
#include "Renderer.h"

class IndexBuffer {
private:
	unsigned int m_Renderer_ID;//ID used on a lower level closer to Open GL. To refer directly to the ID of the current command
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetCount() const { return m_Count; }
};