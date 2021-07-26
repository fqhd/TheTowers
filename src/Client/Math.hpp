#pragma once

#include <array>
#include <cstdint>
#include "Mat4.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"

namespace math {

	const float PI = 3.1415926536f;

	// Functions
	mat4 ortho(float left, float right, float bottom, float top);
	mat4 perspective(float fov, float aspect, float zNear, float zFar);
	mat4 view(const vec3& position, const vec3& forward);

	void translate(const vec3& vec, const mat4& src, mat4& dst);
	void rotate(float angle, const vec3& vec, const mat4& src, mat4& dst);
	void scale(const vec3& vec, const mat4& src, mat4& dst);

	vec2 normalize(const vec2& v);
	vec3 cross(const vec3& a, const vec3& b);
	vec3 normalize(const vec3& v);
	vec4 normalize(const vec4& v);

	float dot(const vec3& a, const vec3& b);
	float length(const vec3& v);
	float length(const vec2& v);
	float length(const vec4& v);
	float round(float f, size_t decimals); // Returns rounded float with specified decimals
	float toRadians(float degrees); // Converts degrees to radians
	math::vec3 fabs(const math::vec3& v);
	float fabs(float v);
	int floor(float v);

};
