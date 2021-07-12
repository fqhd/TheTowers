#include "Math.hpp"
#include <cmath>
#include <string>

#include "Mat4.hpp"

namespace math {

	mat4 perspective(float fovy, float aspect, float zNear, float zFar) {
		float const tanHalfFovy = tan(fovy / 2);

		mat4 Result(0);
		Result.m[0][0] = 1 / (aspect * tanHalfFovy);
		Result.m[1][1] = 1 / (tanHalfFovy);
		Result.m[2][2] = zFar / (zFar - zNear);
		Result.m[2][3] = 1;
		Result.m[3][2] = -(zFar * zNear) / (zFar - zNear);
		return Result;
	} 

	// returns float with specified decimals
	float round(double f, size_t decimals) {
		return ((int)(f*pow(10, decimals)))/pow(10, decimals);
	}
};