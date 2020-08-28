#pragma once

extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

extern Doge::Application* CreateApplication();

int main(int argc, char** argv)
{
	Doge::Application* app = CreateApplication();
	{
		while (!glfwWindowShouldClose(app->s_ActiveWindow->GetNativeWindow()))
		{
			float dt = app->s_FrameTime.DeltaTime();

			Doge::Renderer::ClearColor();

			app->OnUpdate(dt);

			Doge::Renderer::DrawIndexed();

			app->s_ActiveWindow->Update();
		}
	}
	delete app;
}