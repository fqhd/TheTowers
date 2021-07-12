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

		base_vec2()
		: x(NULL), y(NULL)
		{}

		float length() {

		}


		const base_vec3<T> operator+(const base_vec3<T>& other) {
			return base_vec3<T>(x+other.x, y+other.y, z+other.z);
		}

		const base_vec3<T> operator+(const T& other) {
			return base_vec3<T>(x+other, y+other, z+other);
		}

		const base_vec3<T> operator-(const base_vec3<T>& other) {
			return base_vec3<T>(x-other.x, y-other.y, z-other.z);
		}

		const base_vec3<T> operator-(const T& other) {
			return base_vec3<T>(x-other, y-other, z-other);
		}

		const base_vec3<T> operator*(const base_vec3<T>& other) {
			return base_vec3<T>(x*other.x, y*other.y, z*other.z);
		}

		const base_vec3<T> operator*(const T& other) {
			return base_vec3<T>(x*other, y*other, z*other);
		}

		const base_vec3<T> operator/(const base_vec3<T>& other) {
			return base_vec3<T>(x/other.x, y/other.y, z/other.z);
		}

		const base_vec3<T> operator/(const T& other) {
			return base_vec3<T>(x/other, y/other, z/other);
		}
	};

	typedef base_vec3<float> vec3;
	typedef base_vec3<int> ivec3;
	typedef base_vec3<unsigned int> uvec3;
}
