#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	virtual ~Camera() = default;
};

class OrthographicCamera : public Camera
{
public:
	OrthographicCamera(float left, float right, float bottom, float top);
	virtual ~OrthographicCamera() = default;

	void SetPosition(const glm::vec3& position);

	inline const glm::vec3& GetPosition() const { return m_Position; }
	inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
private:
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	// To cache common multiplication of Projection and View
	glm::mat4 m_ViewProjectionMatrix;

	glm::vec3 m_Position;
};

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(float fov, float aspect);
	virtual ~PerspectiveCamera() = default;

	void SetPosition(const glm::vec3& position);

	inline const glm::vec3& GetPosition() const { return m_Position; }
	inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

private:
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	// To cache common multiplication of Projection and View
	glm::mat4 m_ViewProjectionMatrix;

	glm::vec3 m_Position;
};