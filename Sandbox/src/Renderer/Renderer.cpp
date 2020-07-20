#include "pch.h"
#include <glad/glad.h>

#include "Renderer.h"
#include "Renderer2D.h"
#include "Renderer3D.h"

std::unique_ptr<Renderer> Renderer::s_Renderer = nullptr;

void Renderer::Init(const RendererMode& mode)
{
	switch (mode)
	{
		case RendererMode::_2D: s_Renderer.reset(new Renderer2D);
								LOG_WARN("Renderer initialization succeed!");
							    return;
		case RendererMode::_3D: s_Renderer.reset(new Renderer3D);
								LOG_WARN("Renderer initialization succeed!");
								return;
	}
	LOG_ASSERT(false, "Renderer initialization failed!");
}

void Renderer::Draw(const OrthographicCamera& camera)
{
	Renderer2D::Draw(camera);
}

void Renderer::Draw(const PerspectiveCamera& camera)
{
	Renderer3D::Draw(camera);
}

void Renderer::PushTriangle(const std::string& name, const std::array<Vertex, 3>& data)
{
	s_Renderer->Submit(name, data);
}

void Renderer::PushTriangleMesh(const std::string& name, const std::initializer_list<std::array<Vertex, 3>>& datas)
{
	s_Renderer->Submit(name, datas);
}

void Renderer::PushQuad(const std::string& name, const std::array<Vertex, 4>& data)
{
	s_Renderer->Submit(name, data);
}

void Renderer::PushQuadMesh(const std::string& name, const std::initializer_list<std::array<Vertex, 4>>& datas)
{
	s_Renderer->Submit(name, datas);
}

void Renderer::ClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
