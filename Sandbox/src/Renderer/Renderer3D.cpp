#include "pch.h"
#include "Renderer3D.h"

constexpr uint32_t MaxQuads = 10000;

Renderer3D::Renderer3D()
{
	// Create Texture array with a default white texture
	m_Meshes.Textures.reset(new Texture);

	// Create VertexArray
	m_Meshes.VAO.reset(new VertexArray);

	// Create new VertexBuffer
	std::shared_ptr<VertexBuffer> vertexBuffer;
	vertexBuffer.reset(new VertexBuffer(MaxQuads * 4 * sizeof(Vertex)));
	vertexBuffer->SetLayout({
		{ ShaderDataType::Float4, "a_Position" },
		{ ShaderDataType::Float3, "a_Normal" },
		{ ShaderDataType::Float4, "a_Color" },
		{ ShaderDataType::Float2, "a_TexCoord" },
		{ ShaderDataType::UInt2 , "a_TexHandle", true}
	});
	m_Meshes.VertexBufferPtr = vertexBuffer;
	m_Meshes.VAO->AddVertexBuffer(vertexBuffer);
	m_Meshes.VertexOffset = 0;

	// Create IndexBuffer
	std::shared_ptr<IndexBuffer> indexBuffer;
	indexBuffer.reset(new IndexBuffer(MaxQuads * 6));
	m_Meshes.IndexBufferPtr = indexBuffer;
	m_Meshes.VAO->AddIndexBuffer(indexBuffer);
	m_Meshes.IndexOffset = 0;

	// Create Shader
	m_Meshes.Program.reset(new Shader("assets/shaders/BindlessTexture.glsl"));

	// Set Shader Properties
	m_Meshes.Program->Bind();
	
	m_Meshes.Program->SetUniformFloat3("u_Light.Ambient", glm::vec3(0.5f));
	m_Meshes.Program->SetUniformFloat3("u_Light.Diffuse", glm::vec3(0.5f));
	m_Meshes.Program->SetUniformFloat3("u_Light.Specular", glm::vec3(1.0f));

	m_Meshes.Program->SetUniformFloat3("u_Material.Ambient", glm::vec3(0.7f));
	m_Meshes.Program->SetUniformFloat3("u_Material.Diffuse", glm::vec3(0.7f));
	m_Meshes.Program->SetUniformFloat3("u_Material.Specular", glm::vec3(0.5f));
	m_Meshes.Program->SetUniformFloat ("u_Material.Shininess", 32.0f);
}

void Renderer3D::PushObject(const std::shared_ptr<SceneObject3D>& object)
{
	if (m_ObjectCache.find(object) == m_ObjectCache.end())
	{
		// Create new VertexBuffer
		if (m_Meshes.VertexOffset >= MaxQuads * 4 * sizeof(Vertex))
		{
			std::shared_ptr<VertexBuffer> vertexBuffer;
			vertexBuffer.reset(new VertexBuffer(MaxQuads * 4 * sizeof(Vertex)));
			vertexBuffer->SetLayout({
				{ ShaderDataType::Float4, "a_Position" },
				{ ShaderDataType::Float3, "a_Normal" },
				{ ShaderDataType::Float4, "a_Color" },
				{ ShaderDataType::Float2, "a_TexCoord" },
				{ ShaderDataType::UInt2 , "a_TexHandle", true}
			});
			m_Meshes.VertexBufferPtr = vertexBuffer;
			m_Meshes.VAO->AddVertexBuffer(vertexBuffer);
			m_Meshes.VertexOffset = 0;

			std::shared_ptr<IndexBuffer> indexBuffer;
			indexBuffer.reset(new IndexBuffer(MaxQuads * 6));
			m_Meshes.IndexBufferPtr = indexBuffer;
			m_Meshes.VAO->AddIndexBuffer(indexBuffer);
			m_Meshes.IndexOffset = 0;
		}

		// Insert object into cache
		ObjectMapValue mapObject(object, m_Meshes.VertexBufferPtr, m_Meshes.IndexBufferPtr, m_Meshes.VertexOffset, m_Meshes.IndexOffset);
		m_ObjectCache.insert(std::make_pair(object, mapObject));

		// Push object into VertexArray
		m_Meshes.VertexBufferPtr->SetData(&(object->GetData()[0].Position[0]), m_Meshes.VertexOffset, object->GetVertexSize());
		m_Meshes.VertexOffset += object->GetVertexSize();

		const auto& indices = object->CalculateIndices(m_Meshes.offset);
		m_Meshes.IndexBufferPtr->SetData(indices.data(), m_Meshes.IndexOffset, object->GetIndexCount());
		m_Meshes.IndexOffset += object->GetIndexCount() * sizeof(uint32_t);
	}
}

const uint64_t Renderer3D::AddTexture(const char* path)
{
	return m_Meshes.Textures->LoadTexture(path);
}

const uint64_t Renderer3D::GetDefaultTexture()
{
	return m_Meshes.Textures->DefaultTexture();
}

void Renderer3D::Transform(const std::shared_ptr<SceneObject3D>& object, const glm::mat4& transform)
{
	auto& object_it = m_ObjectCache.find(object);
	if (object_it == m_ObjectCache.end())
	{
		LOG_ERROR("Object does not exist!");
		return;
	}
	// Get object from the Cache and apply transform
	auto& transedObject = object_it->second.Object;
	transedObject->Transform(transform);

	// Update object position with the new transform
	object_it->second.VertexBufferPtr->SetData(&transedObject->GetData()[0].Position[0], object_it->second.VertexOffset, transedObject->GetVertexSize());
}

