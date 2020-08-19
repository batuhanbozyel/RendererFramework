#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	virtual ~Camera() = default;

	virtual void Update() = 0;
	virtual void Move(int keyCode, float dt) {}
	virtual void Rotate(const std::pair<float, float>& mousePos) {}

	inline const glm::vec3& GetPosition() const { return m_Position; }
	inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	inline void SetPosition(const glm::vec3& position) { m_Position = position; }

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
	OrthographicCamera(float width, float height, 
					   const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f));
	virtual ~OrthographicCamera() = default;

	virtual void Update() override;
	virtual void Move(int keyCode, float dt) override;

	virtual void SetProjection(float width, float height) override;
};

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(float fov, float width, float height, 
					  const glm::vec3& position  = glm::vec3(0.0f, 0.0f,  2.0f), 
					  const glm::vec3& front		 = glm::vec3(0.0f, 0.0f, -1.0f), 
					  const glm::vec3& up		 = glm::vec3(0.0f, 1.0f,  0.0f));
	virtual ~PerspectiveCamera() = default;

	virtual void Update() override;
	virtual void Move(int keyCode, float dt) override;
	virtual void Rotate(const std::pair<float, float>& mousePos) override;

	virtual void SetProjection(float width, float height) override;
private:
	glm::vec3 m_Front;
	glm::vec3 m_Up;

	float m_Yaw;
	float m_Pitch;

	float m_Fov;
	float m_AspectRatio;

	std::pair<float, float> m_LastMousePos;
};