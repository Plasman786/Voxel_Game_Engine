#pragma once
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>      // Or glad, not both
#include <GLFW/glfw3.h>   // Always after glew/glad

// Include glm AFTER OpenGL stuff
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "FastNoiseLite.h"
#include <vector>
#include "NoiseGen.h"
#include "VertexData.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#define ASIO_STANDALONE  // Enables standalone mode
#include <asio.hpp>
#include <thread>
//-----------------------------------------------------
//MACROS!
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))
//-----------------------------------------------------

void GLClearError(); //Declare the Clear Error Function
bool GLLogCall(const char* function, const char* file, int line); //Declare the GLLogCall Function

//-----------------------------------------------------
//old vertex buffer layout support


class Renderer {
private:

public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader&shader) const;
	void Clear() const ;
};
