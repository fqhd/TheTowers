#ifndef CAMERA_H
#define CAMERA_H
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include "../Libs/glad.h"
#include "../World/Chunk.hpp"
#include "../Input/InputManager.hpp"
#include "../../Settings.hpp"


class Camera {
public:

	void init();
	void update(float deltaTime);
	void updateProjectionMatrix();

	float getPitch();
	float getYaw();
	const glm::mat4& getProjectionMatrix();
	const glm::mat4& getViewMatrix();
	const glm::vec3& getPosition();
	const glm::vec3& getForward();


private:

	//Private Functions
	void calculateCameraVectors(float deltaTime);
	void movement(float deltaTime);
	void updateViewMatrix();

	float m_pitch = 0.0f;
	float m_yaw = 90.0f;
	glm::vec3 m_forward;
	glm::vec3 m_position;


	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;


};

#endif
