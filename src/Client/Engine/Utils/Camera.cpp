#include "Camera.hpp"
#include "../Input/Window.hpp"
#include "../../../Constants.hpp"

const float NEAR_DIST = 0.1f;
const float FAR_DIST = 1000.0f;
const float FOV = 70.0f;
const float SPEED = 25.0f;

void Camera::init() {
	m_position = glm::vec3(0, 0, 0);
	m_forward = glm::vec3(0.0f, 0.0f, 1.0f);

	updateProjectionMatrix();

}

void Camera::updateProjectionMatrix() {
	m_projectionMatrix = glm::perspective(glm::radians(FOV), Window::getWidth() / (float) Window::getHeight(), NEAR_DIST, FAR_DIST);
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

	if (InputManager::isKeyDown(GLFW_KEY_W)) {
		m_position += forward * SPEED * deltaTime;
	}

	if (InputManager::isKeyDown(GLFW_KEY_S)) {
		m_position -= forward * SPEED * deltaTime;
	}

	if (InputManager::isKeyDown(GLFW_KEY_A)) {
		m_position -= side * SPEED * deltaTime;
	}

	if (InputManager::isKeyDown(GLFW_KEY_D)) {
		m_position += side * SPEED * deltaTime;
	}

	if (InputManager::isKeyDown(GLFW_KEY_LEFT_SHIFT)) {
		m_position.y -= SPEED * deltaTime;
	}

	if (InputManager::isKeyDown(GLFW_KEY_SPACE)) {
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

	m_pitch -= InputManager::getDeltaMousePosition().y * sensibility;
	m_yaw += InputManager::getDeltaMousePosition().x * sensibility;

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