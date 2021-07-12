#pragma once
#include <cstdlib>

namespace math {

	template<typename T>
	struct base_vec2 {
		T x, y;
		base_vec2(T value) 
		: x(value), y(value)
		{}
		base_vec2(T x, T y) 
		: x(x), y(y)
		{}
	};

	typedef base_vec2<float> vec2;
	typedef base_vec2<int> ivec2;
	typedef base_vec2<int8_t> uvec2; 
}