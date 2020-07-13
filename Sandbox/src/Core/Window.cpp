#include "pch.h"
#include "Window.h"

Window::Window(const WindowProps& props)
	: m_Props(props)
{
	GLFWwindow* window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), props.Monitor, props.Share);
	LOG_ASSERT(window, "Window creation failed");
	m_Context.reset(new Context(window));
	SetVSync(props.VSync);
}

Window::~Window()
{
	glfwDestroyWindow(m_Context->GetNativeWindow());
}

void Window::OnUpdate()
{
	m_Context->PollEvents();
	m_Context->SwapBuffers();
}

void Window::SetVSync(bool enabled)
{
	if (m_Props.VSync ^ enabled)
	{
		m_Props.VSync = enabled;
		glfwSwapInterval(enabled);
	}
}