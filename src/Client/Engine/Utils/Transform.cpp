#include "Transform.hpp"

Transform::Transform(){
	m_position = math::vec3(0.0f, 0.0f, 0.0f);
	m_rotation = math::vec3(0.0f, 0.0f, 0.0f);
	m_scale = math::vec3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(const math::vec3& position, const math::vec3& rotation, const math::vec3& scale){
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
}

void Transform::init(const math::vec3& position, const math::vec3& rotation, const math::vec3& scale){
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
}

const math::mat4& Transform::getMatrix() {
	if(!m_needsUpdate){
		return m_matrix;
	}

	math::mat4 positionMatrix = math::translate(m_position);
	math::mat4 rotX = math::rotate(m_rotation.x, math::vec3(1, 0, 0));
	math::mat4 rotY = math::rotate(m_rotation.y, math::vec3(0, 1, 0));
	math::mat4 rotZ = math::rotate(m_rotation.z, math::vec3(0, 0, 1));
	math::mat4 rotationMatrix = rotZ * rotY * rotX;
	math::mat4 scaleMatrix = math::scale(m_scale);

	m_matrix = positionMatrix * rotationMatrix * scaleMatrix;
	return m_matrix;
}

void Transform::setPosition(const math::vec3& position) {
	m_position = position;
	m_needsUpdate = true;
}

void Transform::setRotation(const math::vec3& rotation) {
	m_rotation = rotation;
	m_needsUpdate = true;
}

void Transform::setScale(const math::vec3& scale) {
	m_scale = scale;
	m_needsUpdate = true;
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

void Transform::move(const math::vec3& delta){
	m_position += delta;
	m_needsUpdate = true;
}
