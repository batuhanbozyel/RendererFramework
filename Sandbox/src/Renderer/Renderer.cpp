#include "pch.h"
#include <glad/glad.h>
#include "Renderer.h"

void Renderer::Init()
{
	Renderer2D::Init();
	LOG_WARN("Renderer initialization succeed!");
}

void Renderer::Draw(const OrthographicCamera& camera)
{
	Renderer2D::Draw(camera);
}

void Renderer::Submit(const std::string& name, const std::initializer_list<std::array<Vertex, 3>>& datas)
{
	Renderer2D::Submit(name, datas);
}

void Renderer::Submit(const std::string& name, const std::array<Vertex, 3>& data)
{
	Renderer2D::Submit(name, data);
}

void Renderer::Submit(const std::string& name, const std::initializer_list<std::array<Vertex, 4>>& datas)
{
	Renderer2D::Submit(name, datas);
}

void Renderer::Submit(const std::string& name, const std::array<Vertex, 4>& data)
{
	Renderer2D::Submit(name, data);
}

void Renderer::ClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
