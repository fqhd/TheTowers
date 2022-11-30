#include "Camera.hpp"
#include <cmath>

const float NEAR_DIST = 0.1f;
const float FAR_DIST = 1000.0f;
const float FOV = 70.0f;

void Camera::init(Config* _config) {
	m_config = _config;
	m_forward = glm::vec3(1, 0, 0);
	m_projectionMatrix = glm::perspective(glm::radians(FOV), _config->getWindowWidth() / (float)_config->getWindowHeight(), NEAR_DIST, FAR_DIST);
}

void Camera::calculateCameraVectors() {
	glm::vec2 previousMousePos = InputManager::getPreviousMousePosition();
	glm::vec2 currentMousePos = InputManager::getMousePosition();

	glm::vec2 deltaMousePos = previousMousePos - currentMousePos;

	m_pitch -= deltaMousePos.y * m_config->getMouseSensitivity();
	m_yaw -= deltaMousePos.x * m_config->getMouseSensitivity();

	if (m_pitch >= 89.0f) {
		m_pitch = 89.0f;
	}
	if (m_pitch <= -89.0f) {
		m_pitch = -89.0f;
	}

	m_forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_forward.y = sin(glm::radians(m_pitch));
	m_forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_forward = glm::normalize(m_forward);
}

const glm::mat4& Camera::getViewMatrix() const {
	return m_viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const {
	return m_projectionMatrix;
}

const glm::vec3& Camera::getPosition() const {
	return m_position;
}

void Camera::setPosition(const glm::vec3& vec) {
	m_position = vec;
}

const glm::vec3& Camera::getForward() const {
	return m_forward;
}

void Camera::setForward(const glm::vec3& forward) {
	m_forward = forward;
}

void Camera::updateViewMatrix() {
	m_viewMatrix = glm::lookAt(m_position, m_forward, glm::vec3(0.0f, 1.0f, 0.0f));
}

float Camera::getPitch() const {
	return m_pitch;
}

float Camera::getYaw() const {
	return m_yaw;
}
