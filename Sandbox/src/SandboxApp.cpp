#include "Doge.h"

class SandboxApp : public Application
{
public:
	virtual void OnStart() override
	{
		const Shader* shader = ShaderLibrary::CreateShader("assets/shaders/PhongLighting.glsl");

		std::shared_ptr<Material> material = std::make_shared<Material>(*shader);
		material->SetBaseColor(glm::vec3(1.0f));
		material->SetBaseShininess(32.0f);

		Model backpack("assets/models/backpack/backpack.obj");
		Model handgun("assets/models/gun/M1911_01.obj");

		RenderData backpackData = RenderDataManager::ConstructBatched(backpack.GetMeshes(), material, glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f)));
		for (uint32_t i = 0; i < 10; i++)
			for (uint32_t j = 0; j < 10; j++)
			{
				backpackData.modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(i*3.0f, j*3.0f, 0.0f));
				m_RenderDatas.push_back(backpackData);
			}
				
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