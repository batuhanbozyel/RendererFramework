#include "pch.h"
#include <glad/glad.h>
#include "Context.h"

bool Context::s_Initialized = false;

static void GLFWErrorCallback(int error, const char* description)
{
	LOG_ERROR("Error: {0}", description);
}

void Context::GLFWInit()
{
	if (!s_Initialized)
	{
		int glfw = glfwInit();
		LOG_ASSERT(glfw, "GLFW initialization failed!");
		s_Initialized = true;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef DEBUG_ENABLED
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

		glfwSetErrorCallback(GLFWErrorCallback);
	}
}

void Context::GLFWTerminate()
{
	if (s_Initialized)
	{
		glfwTerminate();
		s_Initialized = false;
	}
}

void Context::MakeCurrent(GLFWwindow* window)
{
	glfwMakeContextCurrent(window);
	LOG_WARN("Current Context assigned to ID: {0}", (void*)window);
}

Context::Context(GLFWwindow* window)
	: m_Window(window)
{
	GLFWInit();
	LOG_ASSERT(window, "Window could not found!");

	glfwMakeContextCurrent(m_Window);

	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	LOG_ASSERT(status, "Glad initialization failed");

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	LOG_INFO(glGetString(GL_RENDERER));
	LOG_INFO(glGetString(GL_VERSION));

	LOG_WARN("Context creation succeed!");
}

Context::~Context()
{
	m_Window = nullptr;
}

void Context::PollEvents()
{
	glfwPollEvents();
}

void Context::SwapBuffers()
{
	glfwSwapBuffers(m_Window);
}