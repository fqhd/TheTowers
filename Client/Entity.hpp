#ifndef ENTITY_H
#define ENTITY_H

#include "Transform.hpp"
#include "Vertex.hpp"

class Entity {
public:

     Entity(const vec3& c, const Transform& t);

     const vec3& getColor();

     Transform transform;

private:

     vec3 m_color;

};

#endif
