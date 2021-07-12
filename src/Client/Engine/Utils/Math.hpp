#pragma once

#include <array>
#include <cstdlib>
#include "Mat4.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"

namespace math {


	// functions
	mat4 perspective(float fovy, float aspect, float zNear, float zFar);

	// returns float with specified decimals
	float round(float f, size_t decimals);
	float toRadians(float degrees);

};
