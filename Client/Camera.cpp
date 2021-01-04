#include "Camera.hpp"
#include "Constants.hpp"
#include "Window.hpp"


const float NEAR_DIST = 0.1f;
const float FAR_DIST = 1000.0f;
const float FOV = 70.0f;


void Camera::init(const glm::vec3& pos){ m_position = pos;
	m_forward = glm::vec3(0.0f, 0.0f, 1.0f);

	updateProjectionMatrix();


	float ratio = Window::getWidth()/(float)Window::getHeight();
	float nh = 2.0f * glm::tan(FOV / 2.0f) * NEAR_DIST;
	float nw = nh * ratio; 
	float fh = 2.0f * glm::tan(FOV / 2.0f) * FAR_DIST;
	float fw = fh * ratio;

	glm::vec3 dir,nc,fc,X,Y,Z;

	// compute the Z axis of camera
	// this axis points in the opposite direction from 
	// the looking direction
	Z = glm::normalize(getForward());
	Z = glm::normalize(Z);

	// X axis of camera with given "up" vector and Z axis
	X = glm::vec3(0.0f, 1.0f, 0.0f) * Z;
	X = glm::normalize(X);

	// the real "up" vector is the cross product of Z and X
	Y = Z * X;

	// compute the centers of the near and far planes
	nc = getPosition() - Z * NEAR_DIST;
	fc = getPosition() - Z * FAR_DIST;

	pl[0].setNormalAndPoint(-Z,nc);
	pl[1].setNormalAndPoint(Z,fc);

	glm::vec3 aux,normal;

	aux = (nc + Y*nh) - getPosition();
	aux = glm::normalize(aux);
	normal = aux * X;
	pl[2].setNormalAndPoint(normal,nc+Y*nh);

	aux = (nc - Y*nh) - getPosition();
	aux = glm::normalize(aux);
	normal = X * aux;
	pl[3].setNormalAndPoint(normal,nc-Y*nh);
	
	aux = (nc - X*nw) - getPosition();
	aux = glm::normalize(aux);
	normal = aux * Y;
	pl[4].setNormalAndPoint(normal,nc-X*nw);

	aux = (nc + X*nw) - getPosition();
	aux = glm::normalize(aux);
	normal = Y * aux;
	pl[5].setNormalAndPoint(normal,nc+X*nw);


}

void Camera::updateProjectionMatrix(){
	m_projectionMatrix = glm::perspective(glm::radians(FOV), Window::getWidth()/(float)Window::getHeight(), NEAR_DIST, FAR_DIST);
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

     if(m_pitch >= 90.0f){
          m_pitch = 89.0f;
     }
     if(m_pitch <= -90.0f){
          m_pitch = -89.0f;
     }

     m_forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
     m_forward.y = sin(glm::radians(m_pitch));
     m_forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

}

bool Camera::isInView(const glm::vec3& position, float radius){

	//Information to calculate viewing frustum
	for(unsigned int i = 0; i < 6; i++){
		if(glm::dot(position, pl[i].n) + glm::length(pl[i].d) + radius > 0){
			return true;
		}
	}
	

	return false;

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
