#pragma once
#include "Engine/Utils/Vertex.hpp"

class Entity {
public:

	Entity();

	void update(float deltaTime);

	void setTargetPosition(const math::vec3& position);
	void setForward(float pitch, float yaw);
	bool isBlueTeam();


private:

	void updateRotation();

	math::vec3 m_targetPosition;
	float m_targetPitch = 0.0f;
	float m_targetYaw = 0.0f;
	float m_currentPitch = 0.0f;
	float m_currentYaw = 0.0f;
	bool m_isBlueTeam = false;

};
