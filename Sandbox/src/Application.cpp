#include "pch.h"
#include "Application.h"

#include "Renderer/Renderer.h"

Window* Application::s_ActiveWindow = nullptr;
Timestep Application::s_FrameTime = 0.0f;

int main(int argc, char** argv)
{
	Application::Init();

	const std::initializer_list<std::array<Vertex, 3>> myDatas = {
		{
			{{ 0.3f, -0.8f, 0.0f },
			 {-0.1f,  0.1f, 0.0f },
			 { 0.7f , 0.8f, 0.0f }}
		},

		{
			{{ 0.3f, -0.8f, 0.0f },
			 { 0.7f,  0.8f, 0.0f },
			 { 1.1f, -0.8f, 0.0f }}
		},

		{
			{{ 1.1f, -0.8f, 0.0f },
			 { 0.7f,  0.8f, 0.0f },
			 { 1.5f,  0.1f, 0.0f }}
		}
	};

	const std::array<Vertex, 4> squareData = { {
		{-1.5f, -0.8f, 0.0f},
		{-0.5f, -0.8f, 0.0f},
		{-0.5f,  0.2f, 0.0f},
		{-1.5f,  0.2f, 0.0f}
	} };

	Renderer::Submit("Pentagon", myDatas);
	Renderer::Submit("Square", squareData);
	OrthographicCamera camera(-1.6f, 1.6f, -0.9f, 0.9f);
	while (!glfwWindowShouldClose(Application::s_ActiveWindow->GetNativeWindow()))
	{
		Application::DisplayFrameTime();

		Renderer::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Renderer::Clear();

		Renderer::Draw(camera);

		Application::s_ActiveWindow->OnUpdate();
	}

	Application::Shutdown();
}

void Application::Init()
{
	Log::Init();
	Context::GLFWInit();

	Window* window = new Window;
	s_ActiveWindow = window;
	Context::MakeCurrent(s_ActiveWindow->GetNativeWindow());

	Renderer::Init();

	LOG_WARN("Application started running!");
}

void Application::Shutdown()
{
	LOG_WARN("Application terminating!");
	delete s_ActiveWindow;
	Context::GLFWTerminate();
}

void Application::DisplayFrameTime()
{
	std::stringstream title;
	title << Application::s_ActiveWindow->GetWindowProps().Title;
	title << " " << std::setprecision(4) << Application::s_FrameTime.DeltaTime() << "ms";
	glfwSetWindowTitle(Application::s_ActiveWindow->GetNativeWindow(), title.str().c_str());
}

void Application::DisplayFPS()
{
	std::stringstream title;
	title << Application::s_ActiveWindow->GetWindowProps().Title;
	title << " " << (uint32_t)(1.0f / (Application::s_FrameTime.DeltaTime() / 1000.0f)) << " FPS";
	glfwSetWindowTitle(Application::s_ActiveWindow->GetNativeWindow(), title.str().c_str());
}