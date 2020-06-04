#pragma once
//#include<GL/glew.h>
#include <glad\glad.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"



class Renderer
{
public:
	void Clear() const;
	void DepthEnable() const;

	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void DrawArray(const VertexArray& va, const Shader& shader, const unsigned int count) const;
};