#pragma once
#include "Renderer.h"

class Renderer2D : public Renderer
{
public:
	Renderer2D();
	~Renderer2D();

private:
	using ObjectMapValue = std::pair<std::shared_ptr<VertexBuffer>, uint32_t>;
	static std::unordered_map<std::string, ObjectMapValue> s_TriangleMap;
	static std::unordered_map<std::string, ObjectMapValue> s_QuadMap;

};