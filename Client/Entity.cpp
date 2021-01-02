#include "Entity.hpp"

Entity::Entity(const vec3& c, const Transform& t){
     transform = t;
     m_color = c;
}

const vec3& Entity::getColor(){
     return m_color;
}
