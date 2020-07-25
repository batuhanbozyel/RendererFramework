#pragma once
#include <GLFW/glfw3.h>

class Timestep
{
public:
	Timestep(float time)
		: m_LastFrameTime(time) {}

	inline float DeltaTime()
	{
		float time = (float)glfwGetTime();
		m_DeltaTime = time - m_LastFrameTime;
		m_LastFrameTime = time;
		return m_DeltaTime * 1000;
	}

	inline float GetDeltaTime() { return m_DeltaTime * 1000; }
private:
	float m_LastFrameTime = 0.0f;
	float m_DeltaTime = 0.0f;
};