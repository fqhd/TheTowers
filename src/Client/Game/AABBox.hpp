#pragma once

#include <glm/glm.hpp>

struct AABB {
	AABB(){}
	AABB(const glm::vec3& _position, const glm::vec3& _size){
		position = _position;
		size = _size;
	}
	glm::vec3 position;
	glm::vec3 size;
};