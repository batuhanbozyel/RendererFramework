#include "pch.h"
#include "Mesh.h"

std::shared_ptr<Mesh> Mesh::Create(const MeshType& type)
{
	switch (type)
	{
		case MeshType::TRIANGLE: return std::shared_ptr<TriangleMesh>(new TriangleMesh());
		case MeshType::QUAD:     return std::shared_ptr<QuadMesh>(new QuadMesh());
	}
	LOG_ASSERT(false, "Invalid Mesh type!");
	return nullptr;
}

// Triangle Mesh
constexpr uint32_t MaxTriangles = 5000;

TriangleMesh::TriangleMesh()
{
	s_Offset = 0;
	s_VAO.reset(new VertexArray);

	std::shared_ptr<VertexBuffer> vertexBuffer;
	vertexBuffer.reset(new VertexBuffer(MaxTriangles * 3 * sizeof(Vertex)));
	vertexBuffer->SetLayout({
		{ ShaderDataType::Float3, "a_Position" }
		});
	s_VAO->AddVertexBuffer(vertexBuffer);
	s_VertexBufferPtr = vertexBuffer;

	std::shared_ptr<IndexBuffer> indexBuffer;
	uint32_t* indices = CalculateIndices();
	indexBuffer.reset(new IndexBuffer(indices, MaxTriangles * 3));
	s_VAO->SetIndexBuffer(indexBuffer);
	delete[] indices;

	// Hard coding the shader temporarily
	s_Program.reset(new Shader("assets/shaders/FlatColor.glsl"));
}

void TriangleMesh::Push(const Vertex* data)
{
	if (s_Offset >= MaxTriangles * 3 * sizeof(Vertex))
	{
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(new VertexBuffer(MaxTriangles * 3 * sizeof(Vertex)));
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
			});
		s_VAO->AddVertexBuffer(vertexBuffer);
		s_VertexBufferPtr = vertexBuffer;
		s_Offset = 0;
	}

	s_VertexBufferPtr->SetData(&data->Position[0], s_Offset, 3 * sizeof(Vertex));
	s_Offset += 3 * sizeof(Vertex);
}

uint32_t* TriangleMesh::CalculateIndices()
{
	uint32_t* indices = new uint32_t[MaxTriangles * 3];

	for (uint32_t i = 0; i < MaxTriangles * 3; i++)
		indices[i] = i;

	return indices;
}

// Quad Mesh
constexpr uint32_t MaxQuads = 10000;

QuadMesh::QuadMesh()
{
	s_Offset = 0;
	s_VAO.reset(new VertexArray);

	std::shared_ptr<VertexBuffer> vertexBuffer;
	vertexBuffer.reset(new VertexBuffer(MaxQuads * 4 * sizeof(Vertex)));
	vertexBuffer->SetLayout({
		{ ShaderDataType::Float3, "a_Position" }
		});
	s_VAO->AddVertexBuffer(vertexBuffer);
	s_VertexBufferPtr = vertexBuffer;

	std::shared_ptr<IndexBuffer> indexBuffer;
	uint32_t* indices = CalculateIndices();
	indexBuffer.reset(new IndexBuffer(indices, MaxQuads * 6));
	s_VAO->SetIndexBuffer(indexBuffer);
	delete[] indices;

	// Hard coding the shader temporarily
	s_Program.reset(new Shader("assets/shaders/FlatColor.glsl"));
}

void QuadMesh::Push(const Vertex* data)
{
	if (s_Offset >= MaxTriangles * 4 * sizeof(Vertex))
	{
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(new VertexBuffer(MaxTriangles * 4 * sizeof(Vertex)));
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			});
		s_VAO->AddVertexBuffer(vertexBuffer);
		s_VertexBufferPtr = vertexBuffer;
		s_Offset = 0;
	}

	s_VertexBufferPtr->SetData(&data->Position[0], s_Offset, 4 * sizeof(Vertex));
	s_Offset += 4 * sizeof(Vertex);
}

uint32_t* QuadMesh::CalculateIndices()
{
	uint32_t* indices = new uint32_t[MaxQuads * 6];

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