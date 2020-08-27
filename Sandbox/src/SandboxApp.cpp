#include "Doge.h"

class SandboxApp : public Application
{
public:
	virtual void OnStart() override
	{
		const Shader* shader = ShaderLibrary::CreateShader("assets/shaders/BindlessTexture.glsl");

		std::shared_ptr<Material> material = std::make_shared<Material>(*shader);
		material->SetBaseColor(glm::vec3(1.0f));
		material->SetBaseShininess(32.0f);

// 		uint32_t glassTexture = TextureManager::LoadTexture("assets/textures/glass.png");
// 		uint32_t brickTexture = TextureManager::LoadTexture("assets/textures/brick.png");
// 		uint32_t globeTexture = TextureManager::LoadTexture("assets/textures/globe.jpg");
// 		uint32_t moonTexture = TextureManager::LoadTexture("assets/textures/moon.bmp");
// 
// 		Cuboid glassCube(glm::vec3(1.0f), glassTexture);
// 		Cuboid brickCube(glm::vec3(1.0f), brickTexture);
// 		Sphere globeSphere(1.0f, 36, 36, globeTexture);
// 		Sphere moonSphere(1.0f, 36, 36, moonTexture);

		Model backpack("assets/models/backpack/backpack.obj");
		Model handgun("assets/models/gun/M1911_01.obj");

		RenderData backpackData = RenderDataManager::ConstructBatched(backpack.GetMeshes(), material, glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)));
		RenderData handgunData = RenderDataManager::ConstructBatched(handgun.GetMeshes(), material, glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
 		m_RenderDatas.push_back(backpackData);
		m_RenderDatas.push_back(handgunData);
	}

	virtual void OnUpdate(float dt) override
	{
		if (Input::IsKeyPressed(KEY_W)) Renderer::GetCamera()->Move(KEY_W, dt);
		if (Input::IsKeyPressed(KEY_A))	Renderer::GetCamera()->Move(KEY_A, dt);
		if (Input::IsKeyPressed(KEY_S)) Renderer::GetCamera()->Move(KEY_S, dt);
		if (Input::IsKeyPressed(KEY_D)) Renderer::GetCamera()->Move(KEY_D, dt);

		for (const auto& renderData : m_RenderDatas)
		{
			Renderer::Submit(renderData);
		}
	}
private:
	std::vector<RenderData> m_RenderDatas;
};

Application* CreateApplication()
{
	return new SandboxApp();
}