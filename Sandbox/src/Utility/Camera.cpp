#include "pch.h"
#include "Camera.h"

Camera::Camera(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& position)
	: m_ProjectionMatrix(projection), m_ViewMatrix(view), m_Position(position)
{
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Camera::SetPosition(const glm::vec3& position)
{
	m_Position = position;
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);

	m_ViewMatrix = glm::inverse(transform);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

// Orthographic Camera

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, const glm::vec3& position)
	: Camera(glm::ortho(left, right, bottom, top), glm::mat4(1.0f), position)
{
	
}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
	m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

// Perspective Camera

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, const glm::vec3& position, const glm::vec3& target, const glm::vec3& up)
	: Camera(glm::perspective(glm::radians(fov), aspect, 0.01f, 16.0f), glm::lookAt(position, target, up), position), m_Fov(fov), m_AspectRatio(aspect)
{

}

void PerspectiveCamera::SetProjection(float width, float height)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), width / height, 0.01f, 16.0f);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}