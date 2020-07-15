#pragma once
#include "Renderer.h"

class Renderer3D : public Renderer
{
public:
	Renderer3D();
	~Renderer3D();

	static void Draw(const PerspectiveCamera& camera);

	// Triangle Mesh submits
	virtual void Submit(const std::string& name, const std::initializer_list<std::array<Vertex, 3>>& datas) override;
	virtual void Submit(const std::string& name, const std::array<Vertex, 3>& data) override;

	// Quad Mesh submits
	virtual void Submit(const std::string& name, const std::initializer_list<std::array<Vertex, 4>>& datas) override;
	virtual void Submit(const std::string& name, const std::array<Vertex, 4>& data) override;
private:
	using ObjectMapValue = std::pair<std::shared_ptr<VertexBuffer>, uint32_t>;
	static std::unordered_map<std::string, ObjectMapValue> s_TriangleMap;
	static std::unordered_map<std::string, ObjectMapValue> s_QuadMap;

	static std::vector<std::shared_ptr<Mesh>> s_Meshes;
};