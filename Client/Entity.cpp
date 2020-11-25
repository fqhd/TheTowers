#include "Entity.hpp"

Entity::Entity(const Transform& t, Model* model, const ColorRGBA8& color){
	m_color = color;
	transform = t;
	m_model = model;
}

void Entity::move(const glm::vec3& move){
	transform.setPosition(transform.getPosition() + move);
}

void Entity::render(){
	m_model->render();
}

const ColorRGBA8& Entity::getColor() const {
	return m_color;
}
