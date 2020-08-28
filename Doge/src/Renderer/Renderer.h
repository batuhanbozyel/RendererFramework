#pragma once
#include "RenderDataManager.h"

namespace Doge
{
	class VertexArray;
	class UniformBuffer;
	class VertexBuffer;
	class IndexBuffer;
	class Shader;

	class Camera;
	class Material;
	class SceneObject3D;
	class Model;

	struct WindowProps;

	enum class RendererMode
	{
		_2D, _3D
	};

	class Renderer
	{
	public:
		static void Init(const RendererMode& mode, const WindowProps& props);

		static void Submit(const RenderData& data);
		static void DrawIndexed();

		// Render Commands
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static void SetBackground(const glm::vec4& color);
		static void ClearColor();

		inline static const std::unique_ptr<Camera>& GetCamera() { return s_Camera; }
	private:
		static glm::vec4 s_BackgroundColor;
		static std::unique_ptr<Camera> s_Camera;

		static std::unique_ptr<VertexArray> s_VertexArray;
		static std::unique_ptr<UniformBuffer> s_ViewProjectionUniformBuffer;
		static std::unique_ptr<UniformBuffer> s_LightingUniformBuffer;
		static std::unordered_map<std::shared_ptr<Material>, std::queue<RenderData>> s_RenderQueue;

		static const Shader* s_LastShaderState;
	};
}