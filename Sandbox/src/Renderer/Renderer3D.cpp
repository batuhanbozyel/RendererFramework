#include "pch.h"
#include "Renderer3D.h"

std::unordered_map<std::string, Renderer3D::ObjectMapValue> Renderer3D::s_TriangleMap;
std::unordered_map<std::string, Renderer3D::ObjectMapValue> Renderer3D::s_QuadMap;
std::vector<std::shared_ptr<Mesh>> Renderer3D::s_Meshes;

Renderer3D::Renderer3D()
{
	if (s_Meshes.size() == 0)
	{
		s_Meshes.push_back(Mesh::Create(MeshType::TRIANGLE));
		s_Meshes.push_back(Mesh::Create(MeshType::QUAD));
	}
}

Renderer3D::~Renderer3D()
{

}

void Renderer3D::Draw(const PerspectiveCamera& camera)
{
	for (auto& mesh : s_Meshes)
	{
		mesh->Bind();
		mesh->GetShader()->SetUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		glDrawElements(GL_TRIANGLES, mesh->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}

void Renderer3D::Submit(const std::string& name, const std::initializer_list<std::array<Vertex, 3>>& datas)
{
	if (s_TriangleMap.find(name) == s_TriangleMap.end())
	{
		s_TriangleMap.insert(std::pair<std::string, ObjectMapValue>(name, ObjectMapValue(s_Meshes[0]->GetVertexBufferPtr(), s_Meshes[0]->GetOffset())));
		for (auto& data : datas)
		{
			s_Meshes[0]->Push(&data[0]);
		}
	}
}

void Renderer3D::Submit(const std::string& name, const std::array<Vertex, 3>& data)
{
	if (s_TriangleMap.find(name) == s_TriangleMap.end())
	{
		s_TriangleMap.insert(std::pair<std::string, ObjectMapValue>(name, ObjectMapValue(s_Meshes[0]->GetVertexBufferPtr(), s_Meshes[0]->GetOffset())));

		s_Meshes[0]->Push(&data[0]);
	}
}

void Renderer3D::Submit(const std::string& name, const std::initializer_list<std::array<Vertex, 4>>& datas)
{
	if (s_QuadMap.find(name) == s_QuadMap.end())
	{
		s_QuadMap.insert(std::pair<std::string, ObjectMapValue>(name, ObjectMapValue(s_Meshes[1]->GetVertexBufferPtr(), s_Meshes[1]->GetOffset())));
		for (auto& data : datas)
		{
			s_Meshes[1]->Push(&data[0]);
		}
	}
}

void Renderer3D::Submit(const std::string& name, const std::array<Vertex, 4>& data)
{
	if (s_QuadMap.find(name) == s_QuadMap.end())
	{
		s_QuadMap.insert(std::pair<std::string, ObjectMapValue>(name, ObjectMapValue(s_Meshes[1]->GetVertexBufferPtr(), s_Meshes[1]->GetOffset())));

		s_Meshes[1]->Push(&data[0]);
	}
}
