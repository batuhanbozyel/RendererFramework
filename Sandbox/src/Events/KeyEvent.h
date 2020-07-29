#pragma once
#include "Event.h"

class KeyEvent : public Event
{
public:
	inline int GetKeyCode() const { return m_KeyCode; }

	EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
protected:
	KeyEvent(int keyCode)
		: m_KeyCode(keyCode) {}

	int m_KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(int keyCode, int repeatCount)
		: KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

	inline int GetRepeatCount() const { return m_RepeatCount; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyPressed)
private:
	int m_RepeatCount;
};

class KeyReleasedEvent : public KeyEvent
{
	KeyReleasedEvent(int keyCode)
		: KeyEvent(keyCode) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent
{
	KeyTypedEvent(int keyCode)
		: KeyEvent(keyCode) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyTypedEvent: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyTyped)
};