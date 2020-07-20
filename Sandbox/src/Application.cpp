#include "pch.h"
#include "Application.h"

#include "Renderer/Renderer.h"

#include "../tests/2DTest.h"
#include "../tests/3DTest.h"

static RendererMode s_Mode = RendererMode::_3D;

Window* Application::s_ActiveWindow = nullptr;
Timestep Application::s_FrameTime = 0.0f;

int main(int argc, char** argv)
{
	Application::Init();

	Test3D();
	//OrthographicCamera camera(-1.6f, 1.6f, -0.9f, 0.9f);
	glm::vec3 position(0.0f, 0.0f, 2.0f);
	PerspectiveCamera camera(45.0f, 1.6f / 0.9f, position);
	while (!glfwWindowShouldClose(Application::s_ActiveWindow->GetNativeWindow()))
	{
		Application::DisplayFrameTime();

		Renderer::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Renderer::Clear();

		if		(Input::IsKeyPressed(KEY_A))	 position.x -= 0.005f * Application::s_FrameTime.DeltaTime();
		else if (Input::IsKeyPressed(KEY_D)) position.x += 0.005f * Application::s_FrameTime.DeltaTime();
		else if (Input::IsKeyPressed(KEY_W)) position.y += 0.005f * Application::s_FrameTime.DeltaTime();
		else if (Input::IsKeyPressed(KEY_S)) position.y -= 0.005f * Application::s_FrameTime.DeltaTime();
		else if (Input::IsKeyPressed(KEY_Q)) position.z += 0.005f * Application::s_FrameTime.DeltaTime();
		else if (Input::IsKeyPressed(KEY_E)) position.z -= 0.005f * Application::s_FrameTime.DeltaTime();

		camera.SetPosition(position);

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

	Renderer::Init(s_Mode);

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
	title << s_ActiveWindow->GetWindowProps().Title;
	title << " " << std::setprecision(4) << s_FrameTime.DeltaTime() << "ms";
	glfwSetWindowTitle(s_ActiveWindow->GetNativeWindow(), title.str().c_str());
}

void Application::DisplayFPS()
{
	std::stringstream title;
	title << s_ActiveWindow->GetWindowProps().Title;
	title << " " << (uint32_t)(1.0f / (s_FrameTime.DeltaTime() / 1000.0f)) << " FPS";
	glfwSetWindowTitle(s_ActiveWindow->GetNativeWindow(), title.str().c_str());
}