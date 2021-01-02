#include "Transform.hpp"

Transform::Transform(){
     m_position = glm::vec3(0.0f, 0.0f, 0.0f);
     m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
     m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale){
     m_position = position;
     m_rotation = rotation;
     m_scale = scale;
}

const glm::mat4& Transform::getMatrix() {
     if(!m_needsUpdate)
          return m_matrix;

     glm::mat4 positionMatrix = glm::translate(m_position);
     glm::mat4 rotX = glm::rotate(m_rotation.x, glm::vec3(1, 0, 0));
     glm::mat4 rotY = glm::rotate(m_rotation.y, glm::vec3(0, 1, 0));
     glm::mat4 rotZ = glm::rotate(m_rotation.z, glm::vec3(0, 0, 1));
     glm::mat4 rotationMatrix = rotZ * rotY * rotX;
     glm::mat4 scaleMatrix = glm::scale(m_scale);

     m_matrix = positionMatrix * rotationMatrix * scaleMatrix;
     return m_matrix;
}


void Transform::setPosition(const glm::vec3& position) {
     m_position = position;
     m_needsUpdate = true;
}

void Transform::setRotation(const glm::vec3& rotation) {
     m_rotation = rotation;
     m_needsUpdate = true;
}

void Transform::setScale(const glm::vec3& scale) {
     m_scale = scale;
     m_needsUpdate = true;
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

void Transform::move(const glm::vec3& delta){
     m_position += delta;
}

void Transform::smoothMove(const glm::vec3& destination, float speed){
     m_position += (destination - m_position) * speed;
     m_needsUpdate = true;
}
