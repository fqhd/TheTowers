#include "Math.hpp"
#include <cmath>
#include <string>

#include "Mat4.hpp"

namespace math {

	vec3 cross(vec3 a, vec3 b){
		vec3 r;
		r.x = a.y * b.z - a.z * b.y;
		r.y = b.x * a.z - b.z * a.x;
		r.z = a.x * b.y - a.y * b.x;
		return r;
	}

	mat4 translate(const vec3& vec, const mat4& src){
		mat4 r;

		r.m[3][0] += src.m[0][0] * vec.x + src.m[1][0] * vec.y + src.m[2][0] * vec.z;
		r.m[3][1] += src.m[0][1] * vec.x + src.m[1][1] * vec.y + src.m[2][1] * vec.z;
		r.m[3][2] += src.m[0][2] * vec.x + src.m[1][2] * vec.y + src.m[2][2] * vec.z;
		r.m[3][3] += src.m[0][3] * vec.x + src.m[1][3] * vec.y + src.m[2][3] * vec.z;

		return r;
	}

	mat4 perspective(float fovy, float aspect, float zNear, float zFar) {
		float yScale = (1.0f / tan(toRadians(fovy / 2.0f))) * aspect;
		float xScale = yScale / aspect;
		float frustumLength = zFar - zNear;

		mat4 Result(0);
		Result.m[0][0] = xScale;
		Result.m[1][1] = yScale;
		Result.m[2][2] = -((zFar + zNear) / frustumLength);
		Result.m[2][3] = -1;
		Result.m[3][2] = -((2.0f * zNear * zFar) / frustumLength);
		return Result;
	}

	// returns float with specified decimals
	float round(float f, size_t decimals) {
		return ((int)(f*pow(10, decimals)))/pow(10, decimals);
	}

	float toRadians(float degrees){
		return degrees * M_PI/180.0f;
	}
};
