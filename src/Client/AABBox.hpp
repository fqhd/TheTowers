#pragma once

#include "../Math/Math.hpp"

enum CollisionType {
	X_AXIS, Y_AXIS, Z_AXIS, NONE
};

struct AABB {
	AABB(){}
	AABB(const math::vec3& _position, const math::vec3& _size){
		position = _position;
		size = _size;
	}
	math::vec3 position;
	math::vec3 size;
};