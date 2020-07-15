#include "pch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

// Orthographic Camera

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f), m_Position(0.0f)
{
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::SetPosition(const glm::vec3& position)
{
	m_Position = position;
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);

	m_ViewMatrix = glm::inverse(transform);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

// Perspective Camera

PerspectiveCamera::PerspectiveCamera(float fov, float aspect)
	: m_ProjectionMatrix(glm::perspective(glm::radians(fov), aspect, -1.0f, 1.0f)), m_Position(0.0f, 0.0f, -1.6f)
{
	m_ViewMatrix = glm::lookAt(m_Position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void PerspectiveCamera::SetPosition(const glm::vec3& position)
{
	m_Position = position;
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);

	m_ViewMatrix = glm::inverse(transform);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
