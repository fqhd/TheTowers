#include "Camera.hpp"
#include "Constants.hpp"
#include "Window.hpp"


const float NEAR_DIST = 0.1f;
const float FAR_DIST = 1000.0f;
const float FOV = 70.0f;


void Camera::init(){
	unsigned int maxW = Constants::getLocalWorldWidth() * Constants::getChunkWidth();
	m_position = glm::vec3(maxW / 2, 32, maxW / 2);
	m_forward = glm::vec3(0.0f, 0.0f, 1.0f);

	updateProjectionMatrix();

}

void Camera::updateProjectionMatrix(){
	m_projectionMatrix = glm::perspective(glm::radians(FOV), Window::getWidth()/(float)Window::getHeight(), NEAR_DIST, FAR_DIST);
}

float Camera::getPitch(){
	return m_pitch;
}

float Camera::getYaw(){
	return m_yaw;
}

void Camera::movement(float deltaTime, Settings& settings){

     glm::vec3 forward = glm::normalize(glm::vec3(m_forward.x, 0.0f, m_forward.z));
     glm::vec3 side = glm::normalize(glm::cross(m_forward, glm::vec3(0.0f, 1.0f, 0.0f)));

     if(InputManager::isKeyDown(settings.front)){
          m_position += forward * (float)settings.playerSpeed * deltaTime;
     }

     if(InputManager::isKeyDown(settings.back)){
          m_position -= forward * (float)settings.playerSpeed * deltaTime;
     }

     if(InputManager::isKeyDown(settings.left)){
          m_position -= side * (float)settings.playerSpeed * deltaTime;
     }


     if(InputManager::isKeyDown(settings.right)){
          m_position += side * (float)settings.playerSpeed * deltaTime;
     }

     if(InputManager::isKeyDown(settings.down)){
          m_position.y -= (float)settings.playerSpeed * deltaTime;
     }

     if(InputManager::isKeyDown(settings.up)){
          m_position.y += (float)settings.playerSpeed * deltaTime;
     }

}



void Camera::update(Settings& settings, float deltaTime){

	movement(deltaTime, settings);
	calculateCameraVectors(settings.mouseSensibility);
	updateViewMatrix();

}



void Camera::calculateCameraVectors(float sensibility){

	m_pitch -= InputManager::getDeltaMousePosition().y * sensibility;
	m_yaw += InputManager::getDeltaMousePosition().x * sensibility;

     if(m_pitch >= 89.0f){
          m_pitch = 89.0f;
     }
     if(m_pitch <= -89.0f){
          m_pitch = -89.0f;
     }

     m_forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
     m_forward.y = sin(glm::radians(m_pitch));
     m_forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

}

const glm::mat4& Camera::getViewMatrix(){
	return m_viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix(){
	return m_projectionMatrix;
}

const glm::vec3& Camera::getPosition(){
	return m_position;
}

const glm::vec3& Camera::getForward(){
	return m_forward;
}

void Camera::updateViewMatrix(){
	m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, glm::vec3(0.0f, 1.0f, 0.0f));
}
