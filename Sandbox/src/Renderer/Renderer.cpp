#include "pch.h"
#include <glad/glad.h>

#include "Renderer.h"
//#include "Renderer2D.h"
#include "Renderer3D.h"

#include "Core/Window.h"

std::unique_ptr<Renderer> Renderer::s_Renderer = nullptr;
std::unique_ptr<Camera> Renderer::s_Camera = nullptr;
glm::vec4 Renderer::s_BackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);

void Renderer::Init(const RendererMode& mode, const WindowProps& props)
{
	switch (mode)
	{
		case RendererMode::_2D: //s_Renderer.reset(new Renderer2D);
								s_Camera.reset(new OrthographicCamera((float)props.Width, (float)props.Height));
								LOG_WARN("Renderer2D initialization succeed!");
							    return;
		case RendererMode::_3D: s_Renderer.reset(new Renderer3D);
								s_Camera.reset(new PerspectiveCamera(45.0f, (float)props.Width, (float)props.Height));
								LOG_WARN("Renderer3D initialization succeed!");
								return;
	}
	LOG_ASSERT(false, "Renderer initialization failed!");
}

void Renderer::Draw()
{
	const Meshes& mesh = s_Renderer->GetMeshes();
	mesh.Bind();

	// Get Buffers
	const auto& vertexBuffers = mesh.VAO->GetVertexBuffers();
	const auto& indexBuffers = mesh.VAO->GetIndexBuffers();

	// Make a draw call for each buffer
	for (int i = 0; i < vertexBuffers.size(); i++)
	{
		vertexBuffers[i]->Bind();
		indexBuffers[i]->Bind();
		mesh.Program->SetUniformMat4("u_ViewProjection", s_Camera->GetViewProjectionMatrix());
		mesh.Program->SetUniformFloat3("u_CameraPos", s_Camera->GetPosition());
		mesh.Program->SetUniformFloat3("u_Light.Position", s_Camera->GetPosition());
		glDrawElements(GL_TRIANGLES, mesh.IndexBufferPtr->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}

void Renderer::Push(const std::shared_ptr<SceneObject3D>& object)
{
	s_Renderer->PushObject(object);
}

uint64_t Renderer::CreateTexture(const char* path)
{
	return s_Renderer->AddTexture(path);
}

uint64_t Renderer::DefaultTexture()
{
	return s_Renderer->GetDefaultTexture();
}

void Renderer::TransformObject(const std::shared_ptr<SceneObject3D>& object, const glm::mat4& transform)
{
	s_Renderer->Transform(object, transform);
}

void Renderer::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

void Renderer::SetBackground(const glm::vec4& color)
{
	s_BackgroundColor = color;
}

void Renderer::ClearColor()
{
	glClearColor(s_BackgroundColor.r, s_BackgroundColor.g, s_BackgroundColor.b, s_BackgroundColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}