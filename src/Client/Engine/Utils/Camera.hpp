#pragma once
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include "../World/Chunk.hpp"
#include "../Input/InputManager.hpp"
#include "../Math/Math.hpp"


class Camera {
public:

	void init(InputManager* _manager);
	void update(float deltaTime);
	void updateProjectionMatrix();

	float getPitch();
	float getYaw();
	const math::mat4& getProjectionMatrix();
	const math::mat4& getViewMatrix();
	const math::vec3& getPosition();
	const math::vec3& getForward();


private:

	//Private Functions
	void calculateCameraVectors(float deltaTime);
	void movement(float deltaTime);
	void updateViewMatrix();

	float m_pitch = 0.0f;
	float m_yaw = 90.0f;
	math::vec3 m_forward;
	math::vec3 m_position;

	math::mat4 m_projectionMatrix;
	math::mat4 m_viewMatrix;
	InputManager* m_manager;


};


