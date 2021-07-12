#include "Camera.hpp"

const float NEAR_DIST = 0.1f;
const float FAR_DIST = 1000.0f;
const float FOV = 90.0f;
const float SPEED = 25.5f;

void Camera::init(InputManager* _manager) {
	m_position = glm::vec3(64.0f, 32.0f, 128.0f);
	m_forward = glm::vec3(0.0f, 0.0f, 1.0f);
	m_manager = _manager;

	updateViewMatrix();
	updateProjectionMatrix();
}

void Camera::updateProjectionMatrix() {
	glm::vec2 size = m_manager->getWindowSize();
	m_projectionMatrix = glm::perspective(glm::radians(FOV), size.x / (float)size.y, NEAR_DIST, FAR_DIST);
}

float Camera::getPitch() {
	return m_pitch;
}

float Camera::getYaw() {
	return m_yaw;
}

void Camera::movement(float deltaTime) {

	glm::vec3 forward = glm::normalize(glm::vec3(m_forward.x, 0.0f, m_forward.z));
	glm::vec3 side = glm::normalize(glm::cross(m_forward, glm::vec3(0.0f, 1.0f, 0.0f)));

	if (m_manager->isKeyDown(GLFW_KEY_W)) {
		m_position += forward * SPEED * deltaTime;
	}

	if (m_manager->isKeyDown(GLFW_KEY_S)) {
		m_position -= forward * SPEED * deltaTime;
	}

	if (m_manager->isKeyDown(GLFW_KEY_A)) {
		m_position -= side * SPEED * deltaTime;
	}

	if (m_manager->isKeyDown(GLFW_KEY_D)) {
		m_position += side * SPEED * deltaTime;
	}

	if (m_manager->isKeyDown(GLFW_KEY_LEFT_SHIFT)) {
		m_position.y -= SPEED * deltaTime;
	}

	if (m_manager->isKeyDown(GLFW_KEY_SPACE)) {
		m_position.y += SPEED * deltaTime;
	}
}

void Camera::update(float deltaTime) {
	movement(deltaTime);
	calculateCameraVectors(0.3f);
	updateViewMatrix();
	updateViewFrustum();
}

void Camera::updateViewFrustum(){
	viewFrustum.update(m_projectionMatrix * m_viewMatrix);
}

void Camera::calculateCameraVectors(float sensibility) {
	glm::vec2 deltaMousePos = m_manager->getMousePosition() - m_manager->getPreviousMousePosition();

	m_pitch -= deltaMousePos.y * sensibility;
	m_yaw += deltaMousePos.x * sensibility;

	if (m_pitch >= 89.0f) {
		m_pitch = 89.0f;
	}
	if (m_pitch <= -89.0f) {
		m_pitch = -89.0f;
	}

	m_forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_forward.y = sin(glm::radians(m_pitch));
	m_forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
}

const glm::mat4& Camera::getViewMatrix() {
	return m_viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() {
	return m_projectionMatrix;
}

const glm::vec3& Camera::getPosition() {
	return m_position;
}

const glm::vec3& Camera::getForward() {
	return m_forward;
}

void Camera::updateViewMatrix() {
	m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, glm::vec3(0.0f, 1.0f, 0.0f));
}
