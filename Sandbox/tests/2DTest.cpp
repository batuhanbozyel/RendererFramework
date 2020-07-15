#include "pch.h"
#include "Application.h"
#include "Renderer/Renderer.h"

void Test2D()
{
	const std::initializer_list<std::array<Vertex, 3>> myDatas = {
		{
			Vertex(glm::vec3(0.3f, -0.8f, 0.0f), glm::vec4(0.8f, 0.3f, 0.2f, 1.0f)),
			Vertex(glm::vec3(-0.1f, 0.1f, 0.0f), glm::vec4(0.2f, 0.7f, 0.8f, 1.0f)),
			Vertex(glm::vec3(0.7f,  0.8f, 0.0f), glm::vec4(0.8f, 0.3f, 0.2f, 1.0f)),
		},

		{
			Vertex(glm::vec3(0.3f, -0.8f, 0.0f), glm::vec4(0.8f, 0.3f, 0.2f, 1.0f)),
			Vertex(glm::vec3(0.7f,  0.8f, 0.0f), glm::vec4(0.8f, 0.3f, 0.2f, 1.0f)),
			Vertex(glm::vec3(1.1f, -0.8f, 0.0f), glm::vec4(0.8f, 0.3f, 0.2f, 1.0f)),
		},

		{
			Vertex(glm::vec3(1.1f, -0.8f, 0.0f), glm::vec4(0.8f, 0.3f, 0.2f, 1.0f)),
			Vertex(glm::vec3(0.7f,  0.8f, 0.0f), glm::vec4(0.8f, 0.3f, 0.2f, 1.0f)),
			Vertex(glm::vec3(1.5f,  0.1f, 0.0f), glm::vec4(0.2f, 0.7f, 0.8f, 1.0f)),
		}
	};

	const std::array<Vertex, 4> squareData = { {
		Vertex(glm::vec3(-1.5f, -0.8f, 0.0f), glm::vec4(0.2f, 0.7f, 0.8f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.8f, 0.0f), glm::vec4(0.2f, 0.7f, 0.8f, 1.0f)),
		Vertex(glm::vec3(-0.5f,  0.2f, 0.0f), glm::vec4(0.8f, 0.3f, 0.2f, 1.0f)),
		Vertex(glm::vec3(-1.5f,  0.2f, 0.0f), glm::vec4(0.8f, 0.3f, 0.2f, 1.0f)),
	} };

	Renderer::PushTriangleMesh("Pentagon", myDatas);
	Renderer::PushQuad("Square", squareData);
}