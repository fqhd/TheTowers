#ifndef ENTITY_H
#define ENTITY_H

#include "Transform.hpp"
#include "Vertex.hpp"

class Entity {
public:

     Entity(const vec3& c, const Transform& t);

	void setPosition(const glm::vec3& position);
	void setForward(float pitch, float yaw);

     const vec3& getColor();
	Transform transform;


private:

     vec3 m_color;

};

#endif
