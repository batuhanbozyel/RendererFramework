#include "pch.h"
#include "Renderer2D.h"

std::unordered_map<std::string, Renderer2D::ObjectMapValue> Renderer2D::s_QuadMap;
std::unordered_map<std::string, Renderer2D::ObjectMapValue> Renderer2D::s_TriangleMap;

Renderer2D::Renderer2D()
{

}

Renderer2D::~Renderer2D()
{

}