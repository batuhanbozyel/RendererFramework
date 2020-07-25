#pragma once
#include "Core/Window.h"
#include "Core/Timestep.h"

// Temporary
#include "Utility/Camera.h"

int main(int argc, char** argv);

class Application
{
public:
	static void Init();
	static void Shutdown();

	static void DisplayFrameTimeAndFPS();
	static void DisplayFrameTime();
	static void DisplayFPS();

	inline static const Window* GetActiveWindow() { return s_ActiveWindow; }
private:
	static Timestep s_FrameTime;

	static Window* s_ActiveWindow;
	friend int ::main(int argc, char** argv);
};