#include "pch.h"
#include "Application.h"
#include "Renderer/Renderer.h"

void Test3D()
{
	const std::initializer_list<std::array<Vertex, 4>> cubeData = {
		{
			// Back
			Vertex(glm::vec3(-0.8f, -0.8f,  0.5f), glm::vec4(0.8f, 0.2f, 0.2f, 1.0f)),
			Vertex(glm::vec3( 0.2f, -0.8f,  0.5f), glm::vec4(0.8f, 0.2f, 0.2f, 1.0f)),
			Vertex(glm::vec3( 0.2f,  0.2f,  0.5f), glm::vec4(0.8f, 0.2f, 0.2f, 1.0f)),
			Vertex(glm::vec3(-0.8f,  0.2f,  0.5f), glm::vec4(0.8f, 0.2f, 0.2f, 1.0f)),
		},

		{
			// Left
			Vertex(glm::vec3(-0.8f, -0.8f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
			Vertex(glm::vec3(-0.8f, -0.8f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
			Vertex(glm::vec3(-0.8f,  0.2f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
			Vertex(glm::vec3(-0.8f,  0.2f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
		},

		{
			// Bottom
			Vertex(glm::vec3(-0.8f, -0.8f, -0.5f), glm::vec4(0.2f, 0.2f, 0.8f, 1.0f)),
			Vertex(glm::vec3( 0.2f, -0.8f, -0.5f), glm::vec4(0.2f, 0.2f, 0.8f, 1.0f)),
			Vertex(glm::vec3( 0.2f, -0.8f,  0.5f), glm::vec4(0.2f, 0.2f, 0.8f, 1.0f)),
			Vertex(glm::vec3(-0.8f, -0.8f,  0.5f), glm::vec4(0.2f, 0.2f, 0.8f, 1.0f)),
		},

		{
			// Right
			Vertex(glm::vec3( 0.2f, -0.8f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
			Vertex(glm::vec3( 0.2f, -0.8f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
			Vertex(glm::vec3( 0.2f,  0.2f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
			Vertex(glm::vec3( 0.2f,  0.2f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
		},

		{
			// Top
			Vertex(glm::vec3(-0.8f,  0.2f, -0.5f), glm::vec4(0.2f, 0.2f, 0.8f, 1.0f)),
			Vertex(glm::vec3( 0.2f,  0.2f, -0.5f), glm::vec4(0.2f, 0.2f, 0.8f, 1.0f)),
			Vertex(glm::vec3( 0.2f,  0.2f,  0.5f), glm::vec4(0.2f, 0.2f, 0.8f, 1.0f)),
			Vertex(glm::vec3(-0.8f,  0.2f,  0.5f), glm::vec4(0.2f, 0.2f, 0.8f, 1.0f)),
		},

		{
			// Front
			Vertex(glm::vec3(-0.8f, -0.8f, -0.5f), glm::vec4(0.8f, 0.2f, 0.2f, 1.0f)),
			Vertex(glm::vec3( 0.2f, -0.8f, -0.5f), glm::vec4(0.8f, 0.2f, 0.2f, 1.0f)),
			Vertex(glm::vec3( 0.2f,  0.2f, -0.5f), glm::vec4(0.8f, 0.2f, 0.2f, 1.0f)),
			Vertex(glm::vec3(-0.8f,  0.2f, -0.5f), glm::vec4(0.8f, 0.2f, 0.2f, 1.0f)),
		},
	};

	Renderer::PushQuadMesh("Pentagon", cubeData);
}