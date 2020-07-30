#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	virtual ~Camera() = default;

	void SetPosition(const glm::vec3& position);

	inline const glm::vec3& GetPosition() const { return m_Position; }
	inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	// To be defined in Inherited Camera classes
	virtual void SetProjection(float left, float right, float bottom, float top) {}
	virtual void SetProjection(float width, float height) {}
protected:
	Camera(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& position);

protected:
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	// To cache common multiplication of Projection and View
	glm::mat4 m_ViewProjectionMatrix;

	glm::vec3 m_Position;
};

class OrthographicCamera : public Camera
{
public:
	OrthographicCamera(float left, float right, float bottom, float top, const glm::vec3& position);
	virtual ~OrthographicCamera() = default;

	virtual void SetProjection(float left, float right, float bottom, float top) override;
};

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(float fov, float aspect, 
					  const glm::vec3& position  = glm::vec3(0.0f, 0.0f, 2.0f), 
					  const glm::vec3& target	 = glm::vec3(0.0f), 
					  const glm::vec3& up		 = glm::vec3(0.0f, 1.0f, 0.0f));
	virtual ~PerspectiveCamera() = default;

	virtual void SetProjection(float width, float height) override;
private:
	float m_Fov;
	float m_AspectRatio;
};