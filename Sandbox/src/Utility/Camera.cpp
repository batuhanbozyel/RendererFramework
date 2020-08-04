#include "pch.h"
#include "Camera.h"

Camera::Camera(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& position)
	: m_ProjectionMatrix(projection), m_ViewMatrix(view), m_Position(position)
{
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

// Orthographic Camera

OrthographicCamera::OrthographicCamera(float width, float height, const glm::vec3& position)
	: Camera(glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f), glm::mat4(1.0f), position)
{
	
}

void OrthographicCamera::Update()
{
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::Move(int keyCode, float dt)
{

}

void OrthographicCamera::SetProjection(float width, float height)
{
	m_ProjectionMatrix = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

// Perspective Camera

PerspectiveCamera::PerspectiveCamera(float fov, float width, float height, 
									 const glm::vec3& position, 
									 const glm::vec3& front, 
									 const glm::vec3& up)
	:
	Camera(glm::perspective(glm::radians(fov), width / height, 0.01f, 100.0f), glm::lookAt(position, position + front, up), position), 
	m_Fov(fov), m_AspectRatio(width / height), 
	m_Up(up), m_Front(front),
	m_Yaw(-90.0f), m_Pitch(0.0f),
	m_LastMousePos(width / 2.0f, height / 2.0f)
{

}

void PerspectiveCamera::Update()
{
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void PerspectiveCamera::Move(int keyCode, float dt)
{
	constexpr float speed = 0.002f;
	switch (keyCode)
	{
		case KEY_W:
			m_Position += speed * m_Front * dt;
			break;
		case KEY_S:
			m_Position -= speed * m_Front * dt;
			break;
		case KEY_A:
			m_Position -= speed * glm::normalize(glm::cross(m_Front, m_Up)) * dt;
			break;
		case KEY_D:
			m_Position += speed * glm::normalize(glm::cross(m_Front, m_Up)) * dt;
			break;
	}
}

void PerspectiveCamera::Rotate(const std::pair<float, float>& mousePos)
{
	float xOffset = mousePos.first - m_LastMousePos.first;
	float yOffset = m_LastMousePos.second - mousePos.second;

	m_LastMousePos = mousePos;

	constexpr float sensitivity = 0.05f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	m_Yaw += xOffset;
	m_Pitch += yOffset;

	if (m_Pitch > 89.0f) m_Pitch = 89.0f; 
	if (m_Pitch < -89.0f) m_Pitch = -89.0f;

	glm::vec3 direction; direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)); 
	direction.y = sin(glm::radians(m_Pitch)); 
	direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)); 
	m_Front = glm::normalize(direction);
}

void PerspectiveCamera::SetProjection(float width, float height)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), width / height, 0.01f, 100.0f);
}
