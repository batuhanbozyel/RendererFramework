#include "pch.h"
#include "Window.h"

#include "Doge/Events/KeyEvent.h"
#include "Doge/Events/MouseEvent.h"

namespace Doge
{
	Window::Window(const WindowProps& props)
		: m_Props(props)
	{
		GLFWwindow* windowContext = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), props.Monitor, props.Share);
		LOG_ASSERT(windowContext, "Window creation failed");
		m_Context.reset(new Context(windowContext));

		glfwSetWindowUserPointer(windowContext, &m_Props);
		glfwSwapInterval(props.VSync);

		// KeyPressed, KeyReleased Events
		glfwSetKeyCallback(windowContext, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					props.EventCallback(KeyPressedEvent(key, 0));
					break;
				}
				case GLFW_RELEASE:
				{
					props.EventCallback(KeyReleasedEvent(key));
					break;
				}

				case GLFW_REPEAT:
				{
					props.EventCallback(KeyPressedEvent(key, 1));
					break;
				}
				}
			});

		// KeyTyped Event
		glfwSetCharCallback(windowContext, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);

				props.EventCallback(KeyTypedEvent(keycode));
			});

		// MouseButtonPressed, MouseButtonReleased Events
		glfwSetMouseButtonCallback(windowContext, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					props.EventCallback(MouseButtonPressedEvent(button));
					break;
				}
				case GLFW_RELEASE:
				{
					props.EventCallback(MouseButtonReleasedEvent(button));
					break;
				}
				}
			});

		// MouseMoved Event
		glfwSetCursorPosCallback(windowContext, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);

				props.EventCallback(MouseMovedEvent(static_cast<float>(xPos), static_cast<float>(yPos)));
			});

		// MouseScrolled Event
		glfwSetScrollCallback(windowContext, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);

				props.EventCallback(MouseScrolledEvent(static_cast<float>(xOffset), static_cast<float>(yOffset)));
			});

		// WindowClose Event
		glfwSetWindowCloseCallback(windowContext, [](GLFWwindow* window)
			{
				WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);

				props.EventCallback(WindowCloseEvent());
			});

		// WindowResize Event
		glfwSetWindowSizeCallback(windowContext, [](GLFWwindow* window, int width, int height)
			{
				WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);
				props.Width = static_cast<uint32_t>(width);
				props.Height = static_cast<uint32_t>(height);

				props.EventCallback(WindowResizeEvent(props.Width, props.Height));
			});

		// WindowFocus and WindowLostFocus Events
		glfwSetWindowFocusCallback(windowContext, [](GLFWwindow* window, int focused)
			{
				WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);

				static_cast<bool>(focused) == true ? props.EventCallback(WindowFocusEvent()) : props.EventCallback(WindowLostFocusEvent());
			});

		// WindowMoved Event
		glfwSetWindowPosCallback(windowContext, [](GLFWwindow* window, int xPos, int yPos)
			{
				WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);

				props.EventCallback(WindowMovedEvent(xPos, yPos));
			});
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Context->GetNativeWindow());
	}

	void Window::Update()
	{
		m_Context->PollEvents();
		m_Context->SwapBuffers();
	}

	void Window::WindowResize(WindowResizeEvent& e)
	{
		m_Props.Width = e.GetWidth();
		m_Props.Height = e.GetHeight();
	}

	void Window::SetVSync(bool enabled)
	{
		if (m_Props.VSync ^ enabled)
		{
			m_Props.VSync = enabled;
			glfwSwapInterval(enabled);
		}
	}
}