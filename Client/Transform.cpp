#include "Transform.hpp"

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale){

	m_position = position;
	m_rotation = rotation;
	m_scale = scale;

	m_needsUpdate = true;

}

const glm::mat4& Transform::getMatrix(){

	if(m_needsUpdate){
		glm::mat4 posMatrix = glm::translate(m_position);
		glm::mat4 rotX = glm::rotate(m_rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotY = glm::rotate(m_rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZ = glm::rotate(m_rotation.z, glm::vec3(0, 0, 1));
		glm::mat4 scale = glm::scale(m_scale);

		glm::mat4 rotationMatrix = rotZ * rotY * rotX;

		m_matrix = posMatrix * rotationMatrix * scale;
		m_needsUpdate = false;
	}

	return m_matrix;

}


void Transform::setPosition(const glm::vec3& position){
	m_position = position;
	m_needsUpdate = true;
}

void Transform::setScale(const glm::vec3& scale){
	m_scale = scale;
	m_needsUpdate = true;
}

void Transform::setRotation(const glm::vec3& rotation){
	m_rotation = rotation;
	m_needsUpdate = true;
}

const glm::vec3& Transform::getPosition(){
	return m_position;
}

const glm::vec3& Transform::getScale(){
	return m_scale;
}

const glm::vec3& Transform::getRotation(){
	return m_rotation;
}
