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

		base_vec2()
		{}

		~base_vec2() {}

		base_vec2<T>operator+=(const base_vec2<T>& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		base_vec2<T>operator-=(const base_vec2<T>& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		base_vec2<T>operator*=(const base_vec2<T>& other) {
			x *= other.x;
			y *= other.y;
			return *this;
		}

		base_vec2<T>operator/=(const base_vec2<T>& other) {
			x /= other.x;
			y /= other.y;
			return *this;
		}

		const base_vec2<T> operator+(const base_vec2<T>& other) {
			return base_vec2<T>(x+other.x, y+other.y);
		}

		const base_vec2<T> operator+(const T& other) {
			return base_vec2<T>(x+other, y+other);
		}

		const base_vec2<T> operator-(const base_vec2<T>& other) {
			return base_vec2<T>(x-other.x, y-other.y);
		}

		const base_vec2<T> operator-(const T& other) {
			return base_vec2<T>(x-other, y-other);
		}

		const base_vec2<T> operator*(const base_vec2<T>& other) {
			return base_vec2<T>(x*other.x, y*other.y);
		}

		const base_vec2<T> operator*(const T& other) {
			return base_vec2<T>(x*other, y*other);
		}

		const base_vec2<T> operator/(const base_vec2<T>& other) {
			return base_vec2<T>(x/other.x, y/other.y);
		}

		const base_vec2<T> operator/(const T& other) {
			return base_vec2<T>(x/other, y/other);
		}

	};



	typedef base_vec2<float> vec2;
	typedef base_vec2<int> ivec2;
	typedef base_vec2<unsigned int> uvec2;
}
