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
	m_Meshes.VertexOffset = 0;

	// Create IndexBuffer
	std::shared_ptr<IndexBuffer> indexBuffer;
	indexBuffer.reset(new IndexBuffer(MaxQuads * 6));
	m_Meshes.IndexBufferPtr = indexBuffer;
	m_Meshes.VAO->AddIndexBuffer(indexBuffer);
	m_Meshes.IndexOffset = 0;

	// Create Shader
	m_Meshes.Program.reset(new Shader("assets/shaders/BindlessTexture.glsl"));
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
				{ ShaderDataType::Float4, "a_Color" },
				{ ShaderDataType::Float2, "a_TexCoord" },
				{ ShaderDataType::UInt2 , "a_TexHandle"}
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
		ObjectMapValue mapObject;
		mapObject.Object = object;

		mapObject.VertexBufferPtr = m_Meshes.VertexBufferPtr;
		mapObject.VertexOffset = m_Meshes.VertexOffset;

		mapObject.IndexBufferPtr = m_Meshes.IndexBufferPtr;
		mapObject.IndexOffset = m_Meshes.IndexOffset;
		m_ObjectCache.insert(std::make_pair(object, mapObject));

		// Push object into VertexArray
		m_Meshes.VertexBufferPtr->SetData(&(object->GetData()[0].Position[0]), m_Meshes.VertexOffset, object->GetVertexSize());
		m_Meshes.VertexOffset += object->GetVertexSize();

		const auto& indices = object->CalculateIndices(m_Meshes.offset);
		m_Meshes.IndexBufferPtr->SetData(indices.data(), m_Meshes.IndexOffset, object->GetIndexCount());
		m_Meshes.IndexOffset += object->GetIndexCount() * sizeof(uint32_t);
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
	object_it->second.VertexBufferPtr->SetData(&transedObject->GetData()[0].Position[0], object_it->second.VertexOffset, transedObject->GetVertexSize());
}

