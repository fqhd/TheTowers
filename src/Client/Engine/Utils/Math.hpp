#pragma once

#include <array>
#include <cstdlib>

namespace math {
	// vectors
	struct vec2{
		vec2(float val);
		vec2();
		float v[2];
	};

	struct vec3{
		vec3(float val);
		vec3();
		float v[3];
	};

	struct vec4 {
		vec4(float val);
		vec4();
		float v[4];
	};

    // matrices
	struct mat4 {
		mat4(float n); // inits all values to param f
		float m[4][4]; 
	};

	// functions
	mat4 perspective(float fovy, float aspect, float zNear, float zFar);

};