#pragma once
#include "pch.h"

#define BIT(x) (1 << x)

enum class EventType
{
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

class Event
{
};

class EventDispatcher
{
};