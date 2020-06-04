#include "Renderer.h"
#include "Logger.h"



void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();

	va.Bind();
	ib.Bind();
	

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

}

void Renderer::DrawArray(const VertexArray& va, const Shader& shader, const unsigned int count) const
{
	shader.Bind();

	va.Bind();
	//ib.Bind();


	GLCall(glDrawArrays(GL_TRIANGLES, 0, count));

}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
void Renderer::DepthEnable() const
{
	GLCall(glEnable(GL_DEPTH_TEST));
	
}