#include "pch.h"
#include "SceneObject3D.h"

#include "Renderer/Renderer.h"

Cuboid::Cuboid(glm::vec3 length, const glm::vec4& color, uint64_t handle)
{
	if (handle == 0)
		handle = Renderer::DefaultTexture();
	m_Data.resize(24);
	length = length / 2.0f;
	// Front
	m_Data[0] =  { glm::vec3(-length.x, -length.y,  length.z), color, glm::vec2(0.0f, 0.0f), handle };
	m_Data[1] =  { glm::vec3( length.x, -length.y,  length.z), color, glm::vec2(1.0f, 0.0f), handle };
	m_Data[2] =  { glm::vec3( length.x,  length.y,  length.z), color, glm::vec2(1.0f, 1.0f), handle };
	m_Data[3] =  { glm::vec3(-length.x,  length.y,  length.z), color, glm::vec2(0.0f, 1.0f), handle };
	// Back
	m_Data[4] =  { glm::vec3(-length.x, -length.y, -length.z), color, glm::vec2(0.0f, 0.0f), handle };
	m_Data[5] =  { glm::vec3( length.x, -length.y, -length.z), color, glm::vec2(1.0f, 0.0f), handle };
	m_Data[6] =  { glm::vec3( length.x,  length.y, -length.z), color, glm::vec2(1.0f, 1.0f), handle };
	m_Data[7] =  { glm::vec3(-length.x,  length.y, -length.z), color, glm::vec2(0.0f, 1.0f), handle };
	// Left
	m_Data[8] =  { glm::vec3(-length.x, -length.y, -length.z), color, glm::vec2(0.0f, 0.0f), handle };
	m_Data[9] =  { glm::vec3(-length.x, -length.y,  length.z), color, glm::vec2(1.0f, 0.0f), handle };
	m_Data[10] = { glm::vec3(-length.x,  length.y,  length.z), color, glm::vec2(1.0f, 1.0f), handle };
	m_Data[11] = { glm::vec3(-length.x,  length.y, -length.z), color, glm::vec2(0.0f, 1.0f), handle };
	// Right	
	m_Data[12] = { glm::vec3( length.x, -length.y, -length.z), color, glm::vec2(0.0f, 0.0f), handle };
	m_Data[13] = { glm::vec3( length.x, -length.y,  length.z), color, glm::vec2(1.0f, 0.0f), handle };
	m_Data[14] = { glm::vec3( length.x,  length.y,  length.z), color, glm::vec2(1.0f, 1.0f), handle };
	m_Data[15] = { glm::vec3( length.x,  length.y, -length.z), color, glm::vec2(0.0f, 1.0f), handle };
	// Top
	m_Data[16] = { glm::vec3(-length.x,  length.y, -length.z), color, glm::vec2(0.0f, 0.0f), handle };
	m_Data[17] = { glm::vec3( length.x,  length.y, -length.z), color, glm::vec2(1.0f, 0.0f), handle };
	m_Data[18] = { glm::vec3( length.x,  length.y,  length.z), color, glm::vec2(1.0f, 1.0f), handle };
	m_Data[19] = { glm::vec3(-length.x,  length.y,  length.z), color, glm::vec2(0.0f, 1.0f), handle };
	// Bottom
	m_Data[20] = { glm::vec3(-length.x, -length.y, -length.z), color, glm::vec2(0.0f, 0.0f), handle };
	m_Data[21] = { glm::vec3( length.x, -length.y, -length.z), color, glm::vec2(1.0f, 0.0f), handle };
	m_Data[22] = { glm::vec3( length.x, -length.y,  length.z), color, glm::vec2(1.0f, 1.0f), handle };
	m_Data[23] = { glm::vec3(-length.x, -length.y,  length.z), color, glm::vec2(0.0f, 1.0f), handle };
}

void Cuboid::Transform(const glm::mat4& transform)
{
	for (auto& vertex : m_Data)
	{
		vertex.Position = transform * vertex.Position;
	}
}

