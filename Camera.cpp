#include "Camera.hpp"
#include "Constants.hpp"

void Camera::init(const glm::vec3& pos){

	m_position = pos;
	m_forward = glm::vec3(0.0f, 0.0f, 1.0f);

	m_projectionMatrix = glm::perspective(glm::radians(FOV), SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 1000.0f);

}


const glm::mat4& Camera::getViewMatrix() const {
	return m_viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const {
	return m_projectionMatrix;
}

void Camera::update(sf::Window& window){
	m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, glm::vec3(0.0f, 1.0f, 0.0f));
}
