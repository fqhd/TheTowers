#pragma once
#include <cstdlib>

namespace math {

	template<typename T>
	struct base_vec4 {
		T x, y, z, w;
		base_vec4(T value) 
		: x(value), y(value), z(value), w(value) {}
		base_vec4(T x, T y, T z, T w) 
		: x(x), y(y), z(z), w(w) {}

		base_vec4(){x = 0; y = 0; z = 0; w = 0;}

		~base_vec4(){}

		base_vec4<T>operator+=(const base_vec4<T>& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		base_vec4<T>operator-=(const base_vec4<T>& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		base_vec4<T>operator*=(const base_vec4<T>& other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
			return *this;
		}

		base_vec4<T>operator/=(const base_vec4<T>& other) {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
			return *this;
		}

		base_vec4<T> operator+(const base_vec4<T>& other) const {
			return base_vec4<T>(x+other.x, y+other.y, z+other.z, w+other.w);
		}

		base_vec4<T> operator+(const T& other) const {
			return base_vec4<T>(x+other, y+other, z+other, w+other);
		}
		
		base_vec4<T> operator-(const base_vec4<T>& other) const {
			return base_vec4<T>(x-other.x, y-other.y, z-other.z, w-other.w);
		}

		base_vec4<T> operator-(const T& other) const {
			return base_vec4<T>(x-other, y-other, z-other, w-other);
		}

		base_vec4<T> operator*(const base_vec4<T>& other) const {
			return base_vec4<T>(x*other.x, y*other.y, z*other.z, w*other.w);
		}

		base_vec4<T> operator*(const T& other) const {
			return base_vec4<T>(x*other, y*other, z*other, w*other);
		}

		base_vec4<T> operator/(const base_vec4<T>& other) const {
			return base_vec4<T>(x/other.x, y/other.y, z/other.z, w/other.w);
		}

		base_vec4<T> operator/(const T& other) const {
			return base_vec4<T>(x/other, y/other, z/other, w/other);
		}

		bool operator==(const base_vec4<T>& other){
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		bool operator!=(const base_vec4<T>& other){
			return x != other.x || y != other.y || z != other.z || w != other.w;
		}
	};

	typedef base_vec4<float> vec4;
	typedef base_vec4<int> ivec4;
	typedef base_vec4<unsigned int> uvec4; 
}