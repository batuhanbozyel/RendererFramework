#pragma once
#include "Core/Window.h"
#include "Core/Timestep.h"

int main(int argc, char** argv);

class Application
{
public:
	// Application Initialization and Shutdown Methods
	static void Init();
	static void Shutdown();

	// Application Event Handling Methods
	static void OnEvent(Event& e);

	static bool OnWindowClose(WindowCloseEvent& e);
	static bool OnWindowResize(WindowResizeEvent& e);

	static bool OnKeyPress(KeyPressedEvent& e);
	static bool OnMouseButtonPress(MouseButtonPressedEvent& e);
	static bool OnMouseMove(MouseMovedEvent& e);

	// Application Utility Methods
	static void DisplayFrameTimeAndFPS();

	inline static const Window* GetActiveWindow() { return s_ActiveWindow; }
private:
	static Timestep s_FrameTime;

	static Window* s_ActiveWindow;
	friend int ::main(int argc, char** argv);
};