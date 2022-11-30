#include "Transform.hpp"

Transform::Transform(){
	m_position = glm::vec3(0);
	m_rotation = glm::vec3(0);
	m_scale = glm::vec3(1);
}

void Transform::setPosition(const glm::vec3& _position){
	m_needsUpdate = true;
	m_position = _position;
}

void Transform::setRotation(const glm::vec3& _rotation){
	m_needsUpdate = true;
	m_rotation = _rotation;
}

void Transform::setScale(const glm::vec3& _scale){
	m_needsUpdate = true;
	m_scale = _scale;
}

const glm::vec3& Transform::getPosition() const {
	return m_position;
}

const glm::vec3& Transform::getRotation() const {
	return m_rotation;
}

const glm::vec3& Transform::getScale() const {
	return m_scale;
}

void Transform::move(const glm::vec3& _delta){
	m_needsUpdate = true;
	m_position += _delta;
}

glm::mat4 Transform::getMatrix() const {
	glm::mat4 matrix(1.0f);
	glm::translate(matrix, m_position);
	glm::rotate(matrix, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
	glm::rotate(matrix, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
	glm::rotate(matrix, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
	glm::scale(matrix, m_scale);
	return matrix;
}
