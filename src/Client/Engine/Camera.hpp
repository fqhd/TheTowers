#pragma once

#include "Chunk.hpp"
#include "InputManager.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:

	void init();

	void calculateCameraVectors();
	float getPitch() const;
	float getYaw() const;
	const glm::mat4& getProjectionMatrix() const;
	const glm::mat4& getViewMatrix() const;
	const glm::vec3& getPosition() const;
	const glm::vec3& getForward() const;
	void setForward(const glm::vec3&);
	void setPosition(const glm::vec3& vec);
	void updateViewMatrix();

private:

	float m_pitch = 0.0f;
	float m_yaw = 0.0f;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;

};


