#include "pch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

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
