#pragma once
//#include<GL/glew.h>
#include <glad\glad.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


// DEBUGGING
#define ASSERT(x) if (!(x)) __debugbreak(); 
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError();

bool GLLogCall(const char* funtion, const char* file, int line);
