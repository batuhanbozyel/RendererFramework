#pragma once
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Core/Window.h"

class Timestep;

int main(int argc, char** argv);

class Application
{
public:
	// To be defined in Client
	virtual void OnStart() {};
	virtual void OnUpdate(float dt) {};

	inline static const Window* GetActiveWindow() { return s_ActiveWindow; }
private:
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
private:
	static Timestep s_FrameTime;

	static Window* s_ActiveWindow;
	friend int ::main(int argc, char** argv);
};