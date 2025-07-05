////#include "Triangles.h"
//#include <iostream>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//unsigned int shader;
//unsigned int VAO;
//unsigned int VBO;
////------------------------------------------------------------------------------------------------------------------------------
//static unsigned int compileShader(unsigned int type, const std::string& source) {
//	unsigned int id = glCreateShader(type);
//	const char* src = source.c_str();
//	glShaderSource(id, 1, &src, nullptr);
//	glCompileShader(id);
//	
//	int result;
//	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
//	if (result == GL_FALSE) {
//		int length;
//		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
//		char* message = (char*)alloca(length * sizeof(char));
//		glGetShaderInfoLog(id, length, &length, message);
//		std::cout << "Failed to compile "<< (type == GL_VERTEX_SHADER?"vertex":"fragment") << " shader" << std::endl;
//		std::cout << message << std::endl;
//		glDeleteProgram(id);
//		return 0;
//	}
//
//	return id;
//}
//
//static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) {
//	unsigned int program = glCreateProgram();
//	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
//	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//	glAttachShader(program, vs);
//	glAttachShader(program, fs);
//	glLinkProgram(program);
//	glValidateProgram(program);
//
//	glDeleteShader(vs);
//	glDeleteShader(fs);
//
//	return program;
//}
////------------------------------------------------------------------------------------------------------------------------------
//
//
//void triangleSetup() {
//
//	const char* vertexShader = "#version 330 core\n"
//		"layout (location = 0) in vec4 aPos;\n"
//		"void main()\n"
//		"{\n"
//		"   gl_Position = position;\n"
//		"}\0";
//	const char* fragmentShader = "#version 330 core\n"
//		"out vec4 FragColor;\n"
//		"void main()\n"
//		"{\n"
//		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//		"} \0";
//
//	std::cout << "Hi, This is triangle setup before shaders" << std::endl;
//	unsigned int shader = createShader(vertexShader, fragmentShader);
//	glUseProgram(shader);
//
////	// shaders
////	GLint success;
////	char infoLog[512];
////
////	//vertex
////	unsigned int vertexShaderVariable;
////	vertexShaderVariable = glCreateShader(GL_VERTEX_SHADER);
////	glShaderSource(vertexShaderVariable, 1, &vertexShader, NULL);
////	glCompileShader(vertexShaderVariable);
////
////	std::cout << "Hi, This is triangle setup after vertex shader" << std::endl;
////	// vertex check
////	glGetShaderiv(vertexShaderVariable, GL_COMPILE_STATUS, &success);
////	if (!success)
////	{
////		glGetShaderInfoLog(vertexShaderVariable, 512, NULL, infoLog);
////		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
////	}
////	//fragment
////	unsigned int fragmentShaderVariable;
////	fragmentShaderVariable = glCreateShader(GL_FRAGMENT_SHADER);
////	glShaderSource(fragmentShaderVariable, 1, &fragmentShader, NULL);
////	glCompileShader(fragmentShaderVariable);
////	std::cout << "Hi, This is triangle setup after fragment shader" << std::endl;
////
////	//fragment check
////	glGetShaderiv(fragmentShaderVariable, GL_COMPILE_STATUS, &success);
////	if (!success)
////	{
////		glGetShaderInfoLog(fragmentShaderVariable, 512, NULL, infoLog);
////		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
////
////	}
////	//link
////	shaderProgram = glCreateProgram();
////	glAttachShader(shaderProgram, vertexShaderVariable);
////	glAttachShader(shaderProgram, fragmentShaderVariable);
////	glLinkProgram(shaderProgram);
////	std::cout << "Hi, This is triangle setup after linking shaders" << std::endl;
////
////	// link check
////	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
////	if (!success) {
////		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
////		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
////
////	}
////
////	std::cout << "Hi, This is triangle setup after shaders" << std::endl;
////	glDeleteShader(vertexShaderVariable);
////	glDeleteShader(fragmentShaderVariable);
////
//}
//	void triangleData() {
//	std::cout << "Hi, This is triangle data" << std::endl;
//	//data
//	float positions[6] = {
//		 -0.5f, -0.5f,
//		  0.0f,  0.5f,
//		  0.5f, -0.5f
//	};
//	//start up graphics pipeline
//	//vertex array object
//	glGenVertexArrays(1, &VAO);
//	//vertex buffer object
//
//	glGenBuffers(1, &VBO);
//
//	// bind vao
//	glBindVertexArray(VAO);
//	// vertex buffer object hints and binding
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
//	//vertex attributes
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	
//	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//	glBindVertexArray(0);
//	// uncomment this call to draw in wireframe polygons.
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//};
//
//	void triangleDraw() {
//	std::cout << "Hi, This is triangle draw" << std::endl;
//	//activate shader
//	glUseProgram(shader);
//	//re bind incase something else was bound before
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBindVertexArray(VAO);
//	//draw
//	glDrawArrays(GL_TRIANGLES, 0, 3);
//	glBindVertexArray(0); // no need to unbind it every time 
//
//};