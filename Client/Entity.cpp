#include "Entity.hpp"

Entity::Entity(const Transform& t, Model* model){
	transform = t;
	m_model = model;
}

void Entity::move(const glm::vec3& move){
	transform.setPosition(transform.getPosition() + move);
}

void Entity::render(){
	m_model->render();
}
