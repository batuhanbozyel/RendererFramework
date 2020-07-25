#include "pch.h"
#include "Renderer3D.h"

constexpr uint32_t MaxQuads = 10000;

Renderer3D::Renderer3D()
{
	m_Meshes.Textures.reset(new Texture);

	// Create VertexArray
	m_Meshes.VAO.reset(new VertexArray);

	// Create new VertexBuffer
	std::shared_ptr<VertexBuffer> vertexBuffer;
	vertexBuffer.reset(new VertexBuffer(MaxQuads * 4 * sizeof(Vertex)));
	vertexBuffer->SetLayout({
		{ ShaderDataType::Float4, "a_Position" },
		{ ShaderDataType::Float4, "a_Color" },
		{ ShaderDataType::Float2, "a_TexCoord" },
		{ ShaderDataType::UInt2 , "a_TexHandle", true}
	});
	m_Meshes.VertexBufferPtr = vertexBuffer;
	m_Meshes.VAO->AddVertexBuffer(vertexBuffer);
	m_Meshes.Offset = 0;

	// Create IndexBuffer
	std::shared_ptr<IndexBuffer> indexBuffer;
	std::vector<uint32_t> indices = CalculateIndices();
	indexBuffer.reset(new IndexBuffer(&indices[0], MaxQuads * 6));
	m_Meshes.VAO->SetIndexBuffer(indexBuffer);

	// Create Shader
	m_Meshes.Program.reset(new Shader("assets/shaders/BindlessTexture.glsl"));
}

void Renderer3D::PushObject(const std::shared_ptr<SceneObject3D>& object)
{
	if (m_ObjectCache.find(object) == m_ObjectCache.end())
	{
		// Create new VertexBuffer
		if (m_Meshes.Offset >= MaxQuads * 4 * sizeof(Vertex))
		{
			std::shared_ptr<VertexBuffer> vertexBuffer;
			vertexBuffer.reset(new VertexBuffer(MaxQuads * 4 * sizeof(Vertex)));
			vertexBuffer->SetLayout({
				{ ShaderDataType::Float4, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" },
				{ ShaderDataType::Float2, "a_TexCoord" },
				{ ShaderDataType::UInt2 , "a_TexHandle"}
			});
			m_Meshes.VertexBufferPtr = vertexBuffer;
			m_Meshes.VAO->AddVertexBuffer(vertexBuffer);
			m_Meshes.Offset = 0;
		}

		// Insert object into cache
		ObjectMapValue mapObject;
		mapObject.Object = object;
		mapObject.VertexBufferPtr = m_Meshes.VertexBufferPtr;
		mapObject.Offset = m_Meshes.Offset;
		m_ObjectCache.insert(std::make_pair(object, mapObject));

		// Push object into VertexArray
		m_Meshes.VertexBufferPtr->SetData(&(object->GetData()[0].Position[0]), m_Meshes.Offset, object->GetSize());
		m_Meshes.Offset += object->GetSize();
	}
}

uint64_t Renderer3D::AddTexture(const char* path)
{
	return m_Meshes.Textures->LoadTexture(path);
}

uint64_t Renderer3D::GetDefaultTexture()
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
	auto& transedObject = object_it->second.Object;
	transedObject->Transform(transform);
	object_it->second.VertexBufferPtr->SetData(&transedObject->GetData()[0].Position[0], object_it->second.Offset, transedObject->GetSize());
}

std::vector<uint32_t> Renderer3D::CalculateIndices()
{
	std::vector<uint32_t> indices(MaxQuads * 6);

	uint32_t offset = 0;
	for (uint32_t i = 0; i < MaxQuads; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;
		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	return indices;
}


