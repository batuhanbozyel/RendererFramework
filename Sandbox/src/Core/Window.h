#pragma once
#include "Renderer/Context.h"

struct WindowProps
{
	std::string Title;
	uint32_t Width, Height;
	GLFWmonitor* Monitor;
	GLFWwindow* Share;
	bool VSync;

	WindowProps(const std::string& title = "SandboxApp",
		uint32_t width = 1280, uint32_t height = 720,
		GLFWmonitor* monitor = nullptr,
		GLFWwindow* share = nullptr,
		bool vsync = true)
		: Title(title), Width(width), Height(height), Monitor(monitor), Share(share), VSync(vsync)
	{

	}
};

class Window
{
public:
	Window(const WindowProps& props = WindowProps());
	~Window();

	void OnUpdate();

	void SetVSync(bool enabled);
	inline bool VSync() const { return m_Props.VSync; }

	inline GLFWwindow* GetNativeWindow() const { return m_Context->GetNativeWindow(); }
	inline const WindowProps& GetWindowProps() const { return m_Props; }
private:
	std::unique_ptr<Context> m_Context;
	WindowProps m_Props;
};