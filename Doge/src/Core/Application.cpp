#include "pch.h"
#include "Application.h"

#include "Renderer/Renderer.h"
#include "Utility/Camera.h"

namespace Doge
{
	bool Application::s_ThirdPerson = false;
	constexpr RendererMode RENDER_MODE = RendererMode::_3D;

	Window* Application::s_ActiveWindow = nullptr;
	Timestep Application::s_FrameTime = 0.0f;

	// Application Initialization and Shutdown Methods

	Application::Application(const std::string& appName)
	{
		Log::Init();
		Context::GLFWInit();

		Window* window = new Window(appName);
		window->SetEventCallbackFn(OnEvent);
		s_ActiveWindow = window;
		Context::MakeCurrent(s_ActiveWindow->GetNativeWindow());

		Renderer::Init(RENDER_MODE, s_ActiveWindow->GetWindowProps());

		LOG_TRACE("Application started running!");
	}

	Application::~Application()
	{
		LOG_TRACE("Application terminating!");
		delete s_ActiveWindow;
		Context::GLFWTerminate();
	}

	// Application Event Handling Methods

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(OnWindowClose);
		dispatcher.Dispatch<WindowResizeEvent>(OnWindowResize);
		dispatcher.Dispatch<KeyPressedEvent>(OnKeyPress);
		dispatcher.Dispatch<MouseMovedEvent>(OnMouseMove);
		dispatcher.Dispatch<MouseButtonPressedEvent>(OnMouseButtonPress);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		glfwSetWindowShouldClose(s_ActiveWindow->GetNativeWindow(), GLFW_TRUE);
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		glfwSetWindowSize(s_ActiveWindow->GetNativeWindow(), e.GetWidth(), e.GetHeight());
		s_ActiveWindow->WindowResize(e);

		Renderer::GetCamera()->SetProjection(static_cast<float>(e.GetWidth()), static_cast<float>(e.GetHeight()));
		Renderer::SetViewport(0, 0, e.GetWidth(), e.GetHeight());

		LOG_TRACE(e.ToString());
		return true;
	}

	bool Application::OnKeyPress(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == KEY_ESCAPE)
			glfwSetWindowShouldClose(s_ActiveWindow->GetNativeWindow(), GLFW_TRUE);

		return true;
	}

	bool Application::OnMouseButtonPress(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == MOUSE_BUTTON_2)
		{
			s_ThirdPerson = !s_ThirdPerson;
			if (s_ThirdPerson)
			{
				glfwSetInputMode(s_ActiveWindow->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

				if (glfwRawMouseMotionSupported())
					glfwSetInputMode(s_ActiveWindow->GetNativeWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
			}
			else
			{
				glfwSetInputMode(s_ActiveWindow->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

				if (glfwRawMouseMotionSupported())
					glfwSetInputMode(s_ActiveWindow->GetNativeWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
			}
		}

		return true;
	}

	bool Application::OnMouseMove(MouseMovedEvent& e)
	{
		return true;
	}
}