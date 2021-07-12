#pragma once
#include <cstdlib>

namespace math {

	template<typename T>
	struct base_vec3 {
		T x, y, z;
		base_vec3(T value) 
		: x(value), y(value), z(value)
		{}
		base_vec3(T x, T y, T z) 
		: x(x), y(y), z(z)
		{}
	};

	typedef base_vec3<float> vec3;
	typedef base_vec3<int> ivec3;
	typedef base_vec3<int8_t> uvec3; 
}