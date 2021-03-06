#include "pch.h"
#include "Renderer.h"

#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

#include "Doge/Core/Window.h"

#include "Doge/Utility/Camera.h"
#include "Doge/Utility/Material.h"
#include "Doge/Utility/SceneObject3D.h"

namespace Doge
{
	glm::vec4 Renderer::s_BackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
	std::unique_ptr<Camera> Renderer::s_Camera = nullptr;

	std::unique_ptr<VertexArray> Renderer::s_VertexArray = nullptr;
	std::unique_ptr<UniformBuffer> Renderer::s_ViewProjectionUniformBuffer = nullptr;
	std::unique_ptr<UniformBuffer> Renderer::s_LightingUniformBuffer = nullptr;
	std::unordered_map<std::shared_ptr<Material>, std::queue<RenderData>> Renderer::s_RenderQueue;

	const Shader* Renderer::s_LastShaderState = nullptr;

	void Renderer::Init(const RendererMode& mode, const WindowProps& props)
	{
		TextureManager::Init();

		s_VertexArray.reset(new VertexArray);
		s_VertexArray->Bind();

		s_VertexArray->SetBufferLayout({
			{ ShaderDataType::Float4, "a_Position" },
			{ ShaderDataType::Float3, "a_Normal" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::UInt , "a_TexIndex" }
			}, 0);

		// ViewProjection Uniform Buffer: binding = 1
		s_ViewProjectionUniformBuffer.reset(new UniformBuffer(sizeof(glm::mat4) * 2, 1));
		// Lighting Uniform buffer: binding = 2
		s_LightingUniformBuffer.reset(new UniformBuffer(sizeof(glm::vec4) * 5, 2));

		// Set Lighting properties
		s_LightingUniformBuffer->Bind();
		glm::vec3 ambient(0.5f);
		glm::vec3 diffuse(0.5f);
		glm::vec3 specular(1.0f);
		s_LightingUniformBuffer->SetData(&ambient.x, sizeof(glm::vec3), sizeof(glm::vec4) * 2);
		s_LightingUniformBuffer->SetData(&diffuse.x, sizeof(glm::vec3), sizeof(glm::vec4) * 3);
		s_LightingUniformBuffer->SetData(&specular.x, sizeof(glm::vec3), sizeof(glm::vec4) * 4);

		switch (mode)
		{
		case RendererMode::_2D: 	s_Camera.reset(new OrthographicCamera(static_cast<float>(props.Width), static_cast<float>(props.Height)));
			LOG_TRACE("Renderer2D initialization succeed!");
			break;
		case RendererMode::_3D: 	s_Camera.reset(new PerspectiveCamera(60.0f, static_cast<float>(props.Width), static_cast<float>(props.Height)));
			LOG_TRACE("Renderer3D initialization succeed!");
			break;
		default:					LOG_ASSERT(false, "Renderer initialization failed!");
			break;
		}
	}

	void Renderer::Submit(const RenderData& data)
	{
		s_RenderQueue[data.material].emplace(data);
	}

	void Renderer::DrawIndexed()
	{
		// Set Uniform Buffer properties
		s_ViewProjectionUniformBuffer->Bind();
		s_ViewProjectionUniformBuffer->SetData(&s_Camera->GetViewMatrix()[0], sizeof(glm::mat4), 0);
		s_ViewProjectionUniformBuffer->SetData(&s_Camera->GetProjectionMatrix()[0], sizeof(glm::mat4), sizeof(glm::mat4));

		s_LightingUniformBuffer->Bind();
		s_LightingUniformBuffer->SetData(&s_Camera->GetPosition()[0], sizeof(glm::vec3), 0);
		// Temporary: Light direction is set same as Camera direction
		s_LightingUniformBuffer->SetData(&s_Camera->GetViewDirection()[0], sizeof(glm::vec3), sizeof(glm::vec4));

		for (auto& materialLayer : s_RenderQueue)
		{
			// Set Common Material properties
			const Shader& materialShader = materialLayer.first->GetShaderRef();
			if (s_LastShaderState == nullptr || *s_LastShaderState != materialShader)
			{
				materialShader.Bind();
				s_LastShaderState = &materialShader;
			}
			materialLayer.first->SetSharedUniforms();

			auto& renderQueue = materialLayer.second;
			while (!renderQueue.empty())
			{
				const auto& renderData = renderQueue.front();
				// Set Unique Material properties and the Model matrix
				renderData.material->SetModifiedUniforms();
				renderData.material->GetShaderRef().SetUniformMat4("u_Model", renderData.modelMatrix);

				// Bind Buffers
				uint32_t binding = 0;
				for (const auto& vertexBuffer : renderData.VBOs)
				{
					s_VertexArray->BindVertexBuffer(vertexBuffer, binding);
					binding++;
				}
				s_VertexArray->BindIndexBuffer(renderData.IBO);

				glDrawElements(GL_TRIANGLES, renderData.IBO->GetCount(), GL_UNSIGNED_INT, nullptr);
				renderQueue.pop();
			}
		}
	}

	// Render Commands

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
}