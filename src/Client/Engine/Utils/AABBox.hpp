#pragma once

#include "../Math/Math.hpp"

struct AABB {
	AABB(){}
	AABB(const math::vec3& _position, const math::vec3& _size, float _distance){
		position = _position;
		size = _size;
		distance = _distance;
	}
	math::vec3 position;
	math::vec3 size;
	float distance;
};