#include "pch.h"
#include "Window.h"

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

		props.EventCallback(MouseMovedEvent((float)xPos, (float)yPos));
	});

	// MouseScrolled Event
	glfwSetScrollCallback(windowContext, [](GLFWwindow* window, double xOffset, double yOffset)
	{
		WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);

		props.EventCallback(MouseScrolledEvent((float)xOffset, (float)yOffset));
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
		props.Width = (uint32_t)width;
		props.Height = (uint32_t)height;

		props.EventCallback(WindowResizeEvent((uint32_t)width, (uint32_t)height));
	});
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

void Window::OnWindowResize(WindowResizeEvent& e)
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