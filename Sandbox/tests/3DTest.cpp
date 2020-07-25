#include "pch.h"

#include "Renderer/Renderer.h"

void Test3D()
{
	uint64_t brickTexture = Renderer::CreateTexture("assets/textures/brick.png");
	uint64_t glassTexture = Renderer::CreateTexture("assets/textures/glass.png");

	std::shared_ptr<Cuboid> defaultCube = std::make_shared<Cuboid>(glm::vec3(1.0f), glm::vec4(1.0f));
	std::shared_ptr<Cuboid> brickCube = std::make_shared<Cuboid>(glm::vec3(1.0f), glm::vec4(1.0f), brickTexture);
	std::shared_ptr<Cuboid> glassCube = std::make_shared<Cuboid>(glm::vec3(1.0f), glm::vec4(1.0f), glassTexture);
	
	Renderer::Push(defaultCube);
	Renderer::Push(glassCube);
	Renderer::Push(brickCube);

	Renderer::TransformObject(glassCube, glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)));
	Renderer::TransformObject(brickCube, glm::translate(glm::mat4(1.0f), glm::vec3( 1.0f, 0.0f, 0.0f)));
}