#include "pch.h"
#include "Application.h"

#include "Core/Timestep.h"
#include "Renderer/Renderer.h"
#include "Utility/Camera.h"

extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

extern Application* CreateApplication();

constexpr RendererMode RENDER_MODE = RendererMode::_3D;

static std::atomic<bool> s_RenderBegin = false;
static bool s_ThirdPerson = false;

Window* Application::s_ActiveWindow = nullptr;
Timestep Application::s_FrameTime = 0.0f;

int main(int argc, char** argv)
{
	Application* app = CreateApplication();
	app->Init();

	{
		//auto future = std::async(app->DisplayFrameTimeAndFPS);

		app->OnStart();
		while (!glfwWindowShouldClose(app->s_ActiveWindow->GetNativeWindow()))
		{
			s_RenderBegin = true;
			float dt = app->s_FrameTime.DeltaTime();

			Renderer::ClearColor();

			app->OnUpdate(dt);

			if (s_ThirdPerson) Renderer::GetCamera()->Rotate(Input::GetMousePos());

			Renderer::DrawIndexed();

			app->s_ActiveWindow->Update();
			s_RenderBegin = false;
		}
	}

	app->Shutdown();
	delete app;
}

// Application Initialization and Shutdown Methods

void Application::Init()
{
	Log::Init();
	Context::GLFWInit();

	Window* window = new Window;
	window->SetEventCallbackFn(OnEvent);
	s_ActiveWindow = window;
	Context::MakeCurrent(s_ActiveWindow->GetNativeWindow());

	Renderer::Init(RENDER_MODE, s_ActiveWindow->GetWindowProps());

	LOG_TRACE("Application started running!");
}

void Application::Shutdown()
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

// Application Utility Methods

void Application::DisplayFrameTimeAndFPS()
{
	while (!glfwWindowShouldClose(s_ActiveWindow->GetNativeWindow()))
	{
		if (!s_RenderBegin)
		{
			float dt = s_FrameTime.GetDeltaTime();
			std::stringstream title;
			title << s_ActiveWindow->GetWindowProps().Title;
			title << " " << std::setprecision(4) << static_cast<uint32_t>(1.0f / (dt / 1000.0f)) << " FPS " << dt << " ms";
			glfwSetWindowTitle(s_ActiveWindow->GetNativeWindow(), title.str().c_str());
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
}