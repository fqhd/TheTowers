#ifndef ENTITY_H
#define ENTITY_H

#include "Transform.hpp"
#include "Vertex.hpp"

class Entity {
public:

     Entity();
     Entity(const Transform& t);

     void update(float deltaTime);

	void setTargetPosition(const glm::vec3& position);
	void setForward(float pitch, float yaw);

	Transform transform;


private:

     void updateRotation();

     glm::vec3 m_targetPosition;
     float m_targetPitch = 0.0f;
     float m_targetYaw = 0.0f;
     float m_currentPitch = 0.0f;
     float m_currentYaw = 0.0f;

};

#endif
