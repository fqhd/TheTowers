#include "Transform.hpp"

Transform::Transform(){
	m_position = math::vec3(0);
	m_rotation = math::vec3(0);
	m_scale = math::vec3(1);
}

void Transform::setPosition(const math::vec3& _position){
	m_needsUpdate = true;
	m_position = _position;
}

void Transform::setRotation(const math::vec3& _rotation){
	m_needsUpdate = true;
	m_rotation = _rotation;
}

void Transform::setScale(const math::vec3& _scale){
	m_needsUpdate = true;
	m_scale = _scale;
}

const math::vec3& Transform::getPosition() const {
	return m_position;
}

const math::vec3& Transform::getRotation() const {
	return m_rotation;
}

const math::vec3& Transform::getScale() const {
	return m_scale;
}

void Transform::move(const math::vec3& _delta){
	m_needsUpdate = true;
	m_position += _delta;
}

const math::mat4& Transform::getMatrix() {
	if(m_needsUpdate){
		m_matrix.setIdentity();
		math::translate(m_position, m_matrix, m_matrix);
		math::rotate(math::toRadians(m_rotation.x), math::vec3(1, 0, 0), m_matrix, m_matrix);
		math::rotate(math::toRadians(m_rotation.y), math::vec3(0, 1, 0), m_matrix, m_matrix);
		math::rotate(math::toRadians(m_rotation.z), math::vec3(0, 0, 1), m_matrix, m_matrix);
		math::scale(m_scale, m_matrix, m_matrix);
		return m_matrix;
	}
	return m_matrix;
}
