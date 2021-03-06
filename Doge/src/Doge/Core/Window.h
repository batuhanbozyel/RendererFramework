#pragma once
#include <GLFW/glfw3.h>

#include "Doge/Renderer/Context.h"
#include "Doge/Events/WindowEvent.h"

namespace Doge
{
	struct WindowProps
	{
		WindowProps(const std::string& title = "SandboxApp",
			uint32_t width = 1280, uint32_t height = 720,
			GLFWmonitor* monitor = nullptr,
			GLFWwindow* share = nullptr,
			bool vsync = false)
			: Title(title), Width(width), Height(height), Monitor(monitor), Share(share), VSync(vsync)
		{

		}

		std::string Title;
		uint32_t Width, Height;
		GLFWmonitor* Monitor;
		GLFWwindow* Share;
		bool VSync;

		std::function<void(Event&)> EventCallback;
	};

	class Window
	{
	public:
		Window(const WindowProps& props = WindowProps());
		~Window();

		void Update();
		void WindowResize(WindowResizeEvent& e);

		void SetVSync(bool enabled);
		inline void SetEventCallbackFn(std::function<void(Event&)> callback) { m_Props.EventCallback = callback; }
		inline bool VSync() const { return m_Props.VSync; }

		inline GLFWwindow* GetNativeWindow() const { return m_Context->GetNativeWindow(); }
		inline const WindowProps& GetWindowProps() const { return m_Props; }
	private:
		std::unique_ptr<Context> m_Context;
		WindowProps m_Props;
	};
}