#include "Renderer.h" 
VertexArray::VertexArray() : m_RendererID() {
	glGenVertexArrays(1, &m_RendererID);
}
VertexArray::~VertexArray() {
	glDeleteProgram(m_RendererID);
}
void VertexArray::AddArrayBuffer(Layout layout)  {
	Bind();	
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(
			i, 
			element.count, 
			element.type, 
			element.normalised,
			layout.GetStride(), 
			reinterpret_cast<const void*>(static_cast<uintptr_t>(offset))
		);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}	
}
void VertexArray::Bind() const{
	glBindVertexArray(m_RendererID);
}
void VertexArray::UnBind() const{
	glBindVertexArray(0);
}
