#include "Entity.hpp"

const float ENTITY_MOVEMENT_SHARPNESS = 8.0f;

Entity::Entity() {

}

Entity::Entity(const Transform & t) {
	transform = t;
}

void Entity::update(float deltaTime) {
	float s = ENTITY_MOVEMENT_SHARPNESS;
	transform.move((m_targetPosition - transform.getPosition()) * s * deltaTime);
	m_currentPitch += (m_targetPitch - m_currentPitch) * s * deltaTime;
	m_currentYaw += (m_targetYaw - m_currentYaw) * s * deltaTime;
	updateRotation();
}

void Entity::setTargetPosition(const glm::vec3 & position) {
	m_targetPosition = position;
}

void Entity::setForward(float pitch, float yaw) {
	m_targetPitch = pitch;
	m_targetYaw = yaw;
}

void Entity::updateRotation() {
	transform.setRotation(glm::vec3(glm::radians(-m_currentPitch), glm::radians(-(m_currentYaw - 90)), 0));
}

bool Entity::isBlueTeam(){
	return m_isBlueTeam;
}
