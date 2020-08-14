#include "Doge.h"

class SandboxApp : public Application
{
public:
	virtual void OnStart() override
	{
		uint64_t glassTexture = Renderer::CreateTexture("assets/textures/glass.png");
		uint64_t brickTexture = Renderer::CreateTexture("assets/textures/brick.png");
		uint64_t globeTexture = Renderer::CreateTexture("assets/textures/globe.jpg");
		uint64_t moonTexture = Renderer::CreateTexture("assets/textures/moon.bmp");

		std::shared_ptr<Cuboid> glassCube = std::make_shared<Cuboid>(glm::vec3(1.0f), glm::vec4(1.0f), glassTexture);
		std::shared_ptr<Cuboid> brickCube = std::make_shared<Cuboid>(glm::vec3(1.0f), glm::vec4(1.0f), brickTexture);
		std::shared_ptr<Sphere> globeSphere = std::make_shared<Sphere>(1.0f, 36, 36, glm::vec4(1.0f), globeTexture);
		std::shared_ptr<Sphere> moonSphere = std::make_shared<Sphere>(1.0f, 36, 36, glm::vec4(1.0f), moonTexture);
		std::shared_ptr<Cuboid> orangeCube = std::make_shared<Cuboid>(glm::vec3(1.0f), glm::vec4(0.7f, 0.3f, 0.2f, 1.0f));

		glassCube->Transform(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)));
		brickCube->Transform(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
		globeSphere->Transform(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f)));
		moonSphere->Transform(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, 0.0f)));

		Renderer::Push(glassCube);
		Renderer::Push(brickCube);
		Renderer::Push(globeSphere);
		Renderer::Push(moonSphere);
		Renderer::Push(orangeCube);

		Model backpack("assets/models/backpack/backpack.obj");
		Model handgun("assets/models/handgun/Handgun_obj.obj");
	}

	virtual void OnUpdate(float dt) override
	{
		if (Input::IsKeyPressed(KEY_W)) Renderer::GetCamera()->Move(KEY_W, dt);
		if (Input::IsKeyPressed(KEY_A))	Renderer::GetCamera()->Move(KEY_A, dt);
		if (Input::IsKeyPressed(KEY_S)) Renderer::GetCamera()->Move(KEY_S, dt);
		if (Input::IsKeyPressed(KEY_D)) Renderer::GetCamera()->Move(KEY_D, dt);
	}
};

Application* CreateApplication()
{
	return new SandboxApp();
}