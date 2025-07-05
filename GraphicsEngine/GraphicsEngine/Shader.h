#pragma once
#include "Renderer.h"
#include <unordered_map>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};
class Shader {
private:
	std::string m_filepath;
	unsigned int m_RendererID;
	unsigned int GetUniformLocation(const std::string& filename);
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	std::unordered_map <std::string, unsigned int>m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	void SetUniform4f(const std::string& filename, float v0, float v1, float v2, float v3);
}; 