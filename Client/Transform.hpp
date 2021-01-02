#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/gtx/transform.hpp>

class Transform {
public:

     Transform();
     Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
     const glm::mat4& getMatrix();

     void setPosition(const glm::vec3& position);
     void setRotation(const glm::vec3& rotation);
     void setScale(const glm::vec3& scale);

     void move(const glm::vec3& delta);
     void smoothMove(const glm::vec3& destination, float speed); //Function needs to be ran each frame

     const glm::vec3& getPosition() const;
     const glm::vec3& getRotation() const;
     const glm::vec3& getScale() const;

private:

     bool m_needsUpdate = true;

     glm::vec3 m_position;
     glm::vec3 m_rotation;
     glm::vec3 m_scale;

     glm::mat4 m_matrix;

};

#endif
