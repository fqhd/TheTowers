#include "Camera.hpp"
#include <cmath>

const float NEAR_DIST = 0.1f;
const float FAR_DIST = 1000.0f;
const float FOV = 70.0f;

void Camera::init(Config* _config) {
	m_config = _config;
	m_forward = math::vec3(1, 0, 0);
	m_projectionMatrix = math::perspective(math::toRadians(FOV), _config->getWindowWidth() / (float)_config->getWindowHeight(), NEAR_DIST, FAR_DIST);
}

void Camera::calculateCameraVectors() {
	math::vec2 previousMousePos = InputManager::getPreviousMousePosition();
	math::vec2 currentMousePos = InputManager::getMousePosition();

	math::vec2 deltaMousePos = previousMousePos - currentMousePos;

	m_pitch -= deltaMousePos.y * m_config->getMouseSensitivity();
	m_yaw -= deltaMousePos.x * m_config->getMouseSensitivity();

	if (m_pitch >= 89.0f) {
		m_pitch = 89.0f;
	}
	if (m_pitch <= -89.0f) {
		m_pitch = -89.0f;
	}

	m_forward.x = cos(math::toRadians(m_yaw)) * cos(math::toRadians(m_pitch));
	m_forward.y = sin(math::toRadians(m_pitch));
	m_forward.z = sin(math::toRadians(m_yaw)) * cos(math::toRadians(m_pitch));
	m_forward = math::normalize(m_forward);
}

const math::mat4& Camera::getViewMatrix() const {
	return m_viewMatrix;
}

const math::mat4& Camera::getProjectionMatrix() const {
	return m_projectionMatrix;
}

const math::vec3& Camera::getPosition() const {
	return m_position;
}

void Camera::setPosition(const math::vec3& vec) {
	m_position = vec;
}

const math::vec3& Camera::getForward() const {
	return m_forward;
}

void Camera::setForward(const math::vec3& forward) {
	m_forward = forward;
}

void Camera::updateViewMatrix() {
	m_viewMatrix = math::view(m_position, m_forward);
}

float Camera::getPitch() const {
	return m_pitch;
}

float Camera::getYaw() const {
	return m_yaw;
}
