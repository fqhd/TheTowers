#include "Entity.hpp"

Entity::Entity(){

}

Entity::Entity(const vec3& c, const Transform& t){
     transform = t;
     m_color = c;
}

const vec3& Entity::getColor(){
     return m_color;
}

void Entity::update(float deltaTime){
     transform.move((m_targetPosition - transform.getPosition()) * deltaTime);
     m_currentPitch += (m_targetPitch - m_currentPitch) * deltaTime;
     m_currentYaw += (m_targetYaw - m_currentYaw) * deltaTime;
     updateRotation();
}

void Entity::setTargetPosition(const glm::vec3& position){
     m_targetPosition = position;
}

void Entity::setForward(float pitch, float yaw){
     m_targetPitch = pitch;
     m_targetYaw = yaw;
}

void Entity::updateRotation(){
     transform.setRotation(glm::vec3(glm::radians(-m_currentPitch), glm::radians(-(m_currentYaw - 90)), 0));
}
