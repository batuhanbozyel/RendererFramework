#pragma once
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Window.h"
#include "Timestep.h"

int main(int argc, char** argv);

namespace Doge
{
	class Application
	{
	public:
		Application(const std::string& appName = "Doge");
		~Application();

		// To be defined in Client
		virtual void OnUpdate(float dt) {};

		inline static const Window* GetActiveWindow() { return s_ActiveWindow; }
	private:
		// Application Event Handling Methods
		static void OnEvent(Event& e);

		static bool OnWindowClose(WindowCloseEvent& e);
		static bool OnWindowResize(WindowResizeEvent& e);

		static bool OnKeyPress(KeyPressedEvent& e);
		static bool OnMouseButtonPress(MouseButtonPressedEvent& e);
		static bool OnMouseMove(MouseMovedEvent& e);
	protected:
		static bool s_ThirdPerson;

	private:
		static Timestep s_FrameTime;

		static Window* s_ActiveWindow;

		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}
