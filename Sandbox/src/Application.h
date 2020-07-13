#pragma once
#include "Core/Window.h"

// Temporary
#include "Utility/Camera.h"

int main(int argc, char** argv);

class Application
{
public:
	static void Init();
	static void Shutdown();

	inline static const Window* GetActiveWindow() { return s_ActiveWindow; }
private:
	static Window* s_ActiveWindow;
	friend int ::main(int argc, char** argv);
};