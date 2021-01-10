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

void Entity::setPosition(const glm::vec3& position){
	transform.setPosition(position);
}

void Entity::setForward(float pitch, float yaw){
	transform.setRotation(glm::vec3(glm::radians(-pitch), glm::radians(-(yaw - 90)), 0));
}
