#include "pch.h"

#include "Renderer/Renderer.h"

void Test3D()
{
	uint64_t brickTexture = Renderer::CreateTexture("assets/textures/brick.png");
	uint64_t glassTexture = Renderer::CreateTexture("assets/textures/glass.png");

	std::shared_ptr<Cuboid> orangeCube = std::make_shared<Cuboid>(glm::vec3(1.0f), glm::vec4(0.7f, 0.3f, 0.2f, 1.0f));
	std::shared_ptr<Cuboid> brickCube = std::make_shared<Cuboid>(glm::vec3(1.0f), glm::vec4(1.0f), brickTexture);
	std::shared_ptr<Cuboid> glassCube = std::make_shared<Cuboid>(glm::vec3(1.0f), glm::vec4(1.0f), glassTexture);

	std::shared_ptr<Sphere> testSphere = std::make_shared<Sphere>(1.0f, 36, 36);
	
	Renderer::Push(orangeCube);
 	Renderer::Push(glassCube);
 	Renderer::Push(brickCube);

	Renderer::Push(testSphere);

	Renderer::TransformObject(glassCube, glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)));
	Renderer::TransformObject(brickCube, glm::translate(glm::mat4(1.0f), glm::vec3( 1.0f, 0.0f, 0.0f)));

	Renderer::TransformObject(testSphere, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
}