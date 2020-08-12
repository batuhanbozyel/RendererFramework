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
								s_Camera.reset(new OrthographicCamera(static_cast<float>(props.Width), static_cast<float>(props.Height)));
								LOG_WARN("Renderer2D initialization succeed!");
							    return;
		case RendererMode::_3D: s_Renderer.reset(new Renderer3D);
								s_Camera.reset(new PerspectiveCamera(45.0f, static_cast<float>(props.Width), static_cast<float>(props.Height)));
								LOG_WARN("Renderer3D initialization succeed!");
								return;
	}
	LOG_ASSERT(false, "Renderer initialization failed!");
}

void Renderer::Draw()
{
	const RenderData& data = s_Renderer->GetData();
	data.Bind();

	// Get Buffers
	const auto& vertexBuffers = data.VAO->GetVertexBuffers();
	const auto& indexBuffers = data.VAO->GetIndexBuffers();

	// Make a draw call for each buffer
	int drawCount = 0;
	for (int i = 0; i < vertexBuffers.size(); i++)
	{
		vertexBuffers[i]->Bind();
		indexBuffers[i]->Bind();
		data.Program->SetUniformMat4("u_ViewProjection", s_Camera->GetViewProjectionMatrix());
		data.Program->SetUniformFloat3("u_CameraPos", s_Camera->GetPosition());
		data.Program->SetUniformFloat3("u_Light.Position", s_Camera->GetPosition());
		glDrawElements(GL_TRIANGLES, data.IndexBufferPtr->GetCount(), GL_UNSIGNED_INT, nullptr);
		drawCount++;
	}
	//LOG_TRACE("Draw Calls: {0}", drawCount);
}

void Renderer::Push(const std::shared_ptr<SceneObject3D>& object)
{
	s_Renderer->PushObject(object);
}

const uint64_t Renderer::CreateTexture(const char* path)
{
	return s_Renderer->AddTexture(path);
}

const uint64_t Renderer::DefaultTexture()
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