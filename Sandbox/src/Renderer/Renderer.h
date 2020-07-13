#pragma once
#include "Utility/Mesh.h"
#include <glm/glm.hpp>

class Renderer
{
public:
	static void Init();
	static void Draw(const OrthographicCamera& camera);

	static void Submit(const std::string& name, const std::initializer_list<std::array<Vertex, 3>>& datas);
	static void Submit(const std::string& name, const std::array<Vertex, 3>& data);

	static void Submit(const std::string& name, const std::initializer_list<std::array<Vertex, 4>>& datas);
	static void Submit(const std::string& name, const std::array<Vertex, 4>& data);

	static void ClearColor(const glm::vec4& color);
	static void Clear();
};

