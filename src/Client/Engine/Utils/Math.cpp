#include "Math.hpp"
#include <cmath>

namespace math {

	// vectors

	template<typename T, size_t len> 
	vec<T, len>::vec(T val) {
		for (int i = 0; i < len; i++) { v[i] = val; }
	}



	// mat4 struct
	mat4::mat4(int n) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {m[i][j] = n;}
		}
	}


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

};