#include "Transform.hpp"

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

math::mat4 Transform::getMatrix() const {
	math::mat4 matrix;
	matrix.setIdentity();
	math::translate(m_position, matrix, matrix);
	math::rotate(math::toRadians(m_rotation.x), math::vec3(1, 0, 0), matrix, matrix);
	math::rotate(math::toRadians(m_rotation.y), math::vec3(0, 1, 0), matrix, matrix);
	math::rotate(math::toRadians(m_rotation.z), math::vec3(0, 0, 1), matrix, matrix);
	math::scale(m_scale, matrix, matrix);
	return matrix;
}
