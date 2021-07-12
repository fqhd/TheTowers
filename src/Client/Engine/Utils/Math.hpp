#pragma once

#include <array>
#include <cstdlib>
#include "Mat4.hpp"

namespace math {


	// functions
	mat4 perspective(float fovy, float aspect, float zNear, float zFar);

	// returns float with specified decimals
	float round(double f, size_t decimals);

};