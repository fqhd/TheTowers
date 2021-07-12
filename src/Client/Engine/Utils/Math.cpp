#include "Math.hpp"
#include <cmath>
#include <string>

#include "Mat4.hpp"

namespace math {

	mat4 translate(const vec3& vec, const mat4& matrix){
		mat4 r;

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
