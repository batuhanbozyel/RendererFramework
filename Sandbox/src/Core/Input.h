#pragma once
#include "KeyCodes.h"
#include "MouseButtonCodes.h"

class Input
{
public:
	static bool IsKeyPressed(int keycode);
	static bool IsKeyReleased(int keycode);
	static bool IsKeyRepeated(int keycode);
	static bool IsMouseButtonPressed(int button);
	std::pair<float, float> GetMousePos();
};