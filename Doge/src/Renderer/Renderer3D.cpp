#include "pch.h"
#include "Renderer3D.h"

#include "Shader.h"
#include "VertexArray.h"

#include "Utility/SceneObject3D.h"
#include "Utility/Model.h"

constexpr uint32_t MaxQuads = 10000;

Renderer3D::Renderer3D()
{
	// Create VertexArray
	m_Data.VAO.reset(new VertexArray);

	// Create new VertexBuffer
	std::shared_ptr<VertexBuffer> vertexBuffer;
	vertexBuffer.reset(new VertexBuffer(MaxQuads * 4 * sizeof(Vertex)));
	vertexBuffer->SetLayout({
		{ ShaderDataType::Float4, "a_Position" },
		{ ShaderDataType::Float3, "a_Normal" },
		{ ShaderDataType::Float2, "a_TexCoord" },
		{ ShaderDataType::UInt , "a_TexIndex", true }
	});
	m_Data.VertexBufferPtr = vertexBuffer;
	m_Data.VAO->AddVertexBuffer(vertexBuffer);
	m_Data.VertexOffset = 0;

	// Create IndexBuffer
	std::shared_ptr<IndexBuffer> indexBuffer;
	indexBuffer.reset(new IndexBuffer(MaxQuads * 6));
	m_Data.IndexBufferPtr = indexBuffer;
	m_Data.VAO->AddIndexBuffer(indexBuffer);
	m_Data.IndexOffset = 0;

	// Create Shader
	m_Data.Program.reset(ShaderLibrary::CreateShader("assets/shaders/BindlessTexture.glsl"));

	// Set Shader Properties
	m_Data.Program->Bind();
	
	m_Data.Program->SetUniformFloat3("u_Light.Ambient", glm::vec3(0.5f));
	m_Data.Program->SetUniformFloat3("u_Light.Diffuse", glm::vec3(0.5f));
	m_Data.Program->SetUniformFloat3("u_Light.Specular", glm::vec3(1.0f));

	m_Data.Program->SetUniformFloat ("u_Material.Shininess", 32.0f);
}

void Renderer3D::PushObject(const std::shared_ptr<SceneObject3D>& object)
{
	if (m_ObjectCache.find(object) == m_ObjectCache.end())
	{
		// Create new VertexBuffer
		if (m_Data.VertexOffset >= MaxQuads * 4 * sizeof(Vertex))
		{
			std::shared_ptr<VertexBuffer> vertexBuffer;
			vertexBuffer.reset(new VertexBuffer(MaxQuads * 4 * sizeof(Vertex)));
			vertexBuffer->SetLayout({
				{ ShaderDataType::Float4, "a_Position" },
				{ ShaderDataType::Float3, "a_Normal" },
				{ ShaderDataType::Float2, "a_TexCoord" },
				{ ShaderDataType::UInt , "a_TexIndex", true }
			});
			m_Data.VertexBufferPtr = vertexBuffer;
			m_Data.VAO->AddVertexBuffer(vertexBuffer);
			m_Data.VertexOffset = 0;

			std::shared_ptr<IndexBuffer> indexBuffer;
			indexBuffer.reset(new IndexBuffer(MaxQuads * 6));
			m_Data.IndexBufferPtr = indexBuffer;
			m_Data.VAO->AddIndexBuffer(indexBuffer);
			m_Data.IndexOffset = 0;
		}

		// Insert object into cache
		ObjectMapValue mapObject(object, m_Data.VertexBufferPtr, m_Data.IndexBufferPtr, m_Data.VertexOffset, m_Data.IndexOffset);
		m_ObjectCache.insert(std::make_pair(object, mapObject));

		// Push object into VertexArray
		m_Data.VertexBufferPtr->SetData(&(object->GetData()[0].Position[0]), m_Data.VertexOffset, object->GetVertexSize());
		m_Data.VertexOffset += object->GetVertexSize();

		const auto& indices = object->CalculateIndices(m_Data.offset);
		m_Data.IndexBufferPtr->SetData(indices.data(), m_Data.IndexOffset, object->GetIndexCount());
		m_Data.IndexOffset += object->GetIndexCount() * sizeof(uint32_t);
	}
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

