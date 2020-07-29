#pragma once
#include "Event.h"

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() = default;

	EVENT_CLASS_TYPE(WindowClose)
	EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryWindow)
};

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height) {}

	inline uint32_t GetWidth() const { return m_Width; }
	inline uint32_t GetHeight() const { return m_Height; }

	EVENT_CLASS_TYPE(WindowResize)
	EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryWindow)
private:
	uint32_t m_Width, m_Height;
};

// To be implemented later

class WindowFocusEvent : public Event
{
public:
	WindowFocusEvent() = default;

	EVENT_CLASS_TYPE(WindowFocus)
	EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryWindow)
};

// To be implemented later
class WindowLostFocusEvent : public Event
{
public:
	WindowLostFocusEvent() = default;

	EVENT_CLASS_TYPE(WindowLostFocus)
	EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryWindow)
};

// To be implemented later
class WindowMovedEvent : public Event
{
public:
	WindowMovedEvent() = default;

	EVENT_CLASS_TYPE(WindowMoved)
	EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryWindow)
};