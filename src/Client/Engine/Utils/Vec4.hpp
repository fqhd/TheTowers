#pragma once
#include <cstdlib>

namespace math {

	template<typename T>
	struct base_vec4 {
		T x, y, z, w;
		base_vec4(T value) 
		: x(value), y(value), z(value), w(value)
		{}
		base_vec4(T x, T y, T z, T w) 
		: x(x), y(y), z(z), w(w)
		{}
	};

	typedef base_vec4<float> vec4;
	typedef base_vec4<int> ivec4;
	typedef base_vec4<int8_t> uvec4; 
}