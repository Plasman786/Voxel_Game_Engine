#include "Renderer.h"

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}
//-----------------------------------------------------
static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << " : " << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);//draw
	//
	//Shader.SetUniform4f("u_Color", b, r, g, 1.0f);
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
