#ifndef CAMERA_H
#define CAMERA_H
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include "../World/Chunk.hpp"
#include "../Input/InputManager.hpp"
#include "../Libs/Frustum.hpp"


class Camera {
public:

	void init(InputManager* _manager, unsigned int _ww, unsigned int _wh);
	void update(float deltaTime);
	void updateProjectionMatrix();

	float getPitch();
	float getYaw();
	const glm::mat4& getProjectionMatrix();
	const glm::mat4& getViewMatrix();
	const glm::vec3& getPosition();
	const glm::vec3& getForward();
	Frustum viewFrustum;


private:

	//Private Functions
	void calculateCameraVectors(float deltaTime);
	void movement(float deltaTime);
	void updateViewMatrix();
	void updateViewFrustum();

	float m_pitch = 0.0f;
	float m_yaw = 90.0f;
	glm::vec3 m_forward;
	glm::vec3 m_position;

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
	InputManager* m_manager;


};

#endif
