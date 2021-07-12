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
	mat4 translate(const vec3& vec, const mat4& matrix);
	vec3 cross(const vec3& a, const vec3& b);
	float length(const vec3& v);
	float length(const vec2& v);
	float length(const vec4& v);
	float round(float f, size_t decimals); // Returns rounded float with specified decimals
	float toRadians(float degrees); // Converts degrees to radians

};
