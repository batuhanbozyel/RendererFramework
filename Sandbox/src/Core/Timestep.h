#pragma once
#include <GLFW/glfw3.h>

class Timestep
{
public:
	Timestep(float time)
		: m_LastFrameTime(time) {}

	float DeltaTime()
	{
		float time = (float)glfwGetTime();
		float deltaTime = time - m_LastFrameTime;
		m_LastFrameTime = time;
		return deltaTime * 1000;
	}
private:
	float m_LastFrameTime = 0.0f;
};