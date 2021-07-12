#include "Math.hpp"
#include <cmath>
#include <string>

#include "Mat4.hpp"

namespace math {

	mat4 view(const vec3& position, float pitch, float yaw){
		mat4 r;
		r.setIdentity();
		r = rotate(toRadians(pitch), vec3(1, 0, 0), r);
		r = rotate(toRadians(yaw), vec3(0, 1, 0), r);
		r = translate(-position, r);
		return r;
	}

	mat4 rotate(float angle, const vec3& axis, const mat4& matrix){
		mat4 r;

		float c = (float)cos(angle);
		float s = (float)sin(angle);

		float oneminusc = 1.0f - c;
		float xy = axis.x * axis.y;
		float yz = axis.y * axis.z;
		float xz = axis.x * axis.z;
		float xs = axis.x * s;
		float ys = axis.y * s;
		float zs = axis.z * s;

		float f00 = axis.x * axis.x * oneminusc+c;
		float f01 = xy * oneminusc + zs;
		float f02 = xz * oneminusc - ys;

		float f10 = xy * oneminusc - zs;
		float f11 = axis.y * axis.y * oneminusc + c;
		float f12 = yz * oneminusc + xs;

		float f20 = xz * oneminusc + ys;
		float f21 = yz * oneminusc - xs;
		float f22 = axis.z * axis.z * oneminusc + c;

		float t00 = matrix.m[0][0] * f00 + matrix.m[1][0] * f01 + matrix.m[2][0] * f02;
		float t01 = matrix.m[0][1] * f00 + matrix.m[1][1] * f01 + matrix.m[2][1] * f02;
		float t02 = matrix.m[0][2] * f00 + matrix.m[1][2] * f01 + matrix.m[2][2] * f02;
		float t03 = matrix.m[0][3] * f00 + matrix.m[1][3] * f01 + matrix.m[2][3] * f02;
		float t10 = matrix.m[0][0] * f10 + matrix.m[1][0] * f11 + matrix.m[2][0] * f12;
		float t11 = matrix.m[0][1] * f10 + matrix.m[1][1] * f11 + matrix.m[2][1] * f12;
		float t12 = matrix.m[0][2] * f10 + matrix.m[1][2] * f11 + matrix.m[2][2] * f12;
		float t13 = matrix.m[0][3] * f10 + matrix.m[1][3] * f11 + matrix.m[2][3] * f12;


		r.m[2][0] = matrix.m[0][0] * f20 + matrix.m[1][0] * f21 + matrix.m[2][0] * f22;
		r.m[2][1] = matrix.m[0][1] * f20 + matrix.m[1][1] * f21 + matrix.m[2][1] * f22;
		r.m[2][2] = matrix.m[0][2] * f20 + matrix.m[1][2] * f21 + matrix.m[2][2] * f22;
		r.m[2][3] = matrix.m[0][3] * f20 + matrix.m[1][3] * f21 + matrix.m[2][3] * f22;
		r.m[0][0] = t00;
		r.m[0][1] = t01;
		r.m[0][2] = t02;
		r.m[0][3] = t03;
		r.m[1][0] = t10;
		r.m[1][1] = t11;
		r.m[1][2] = t12;
		r.m[1][3] = t13;

		return r;
	}

	vec3 cross(vec3 a, vec3 b){
		vec3 r;
		r.x = a.y * b.z - a.z * b.y;
		r.y = b.x * a.z - b.z * a.x;
		r.z = a.x * b.y - a.y * b.x;
		return r;
	}

	mat4 translate(const vec3& vec, const mat4& src){
		mat4 r;

		r.m[3][0] += src.m[0][0] * vec.x + src.m[1][0] * vec.y + src.m[2][0] * vec.z;
		r.m[3][1] += src.m[0][1] * vec.x + src.m[1][1] * vec.y + src.m[2][1] * vec.z;
		r.m[3][2] += src.m[0][2] * vec.x + src.m[1][2] * vec.y + src.m[2][2] * vec.z;
		r.m[3][3] += src.m[0][3] * vec.x + src.m[1][3] * vec.y + src.m[2][3] * vec.z;

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

	vec2 normalize(const vec2& v) {
		float len = length(v);
		return vec2(v.x/len, v.y/len);
	}
	vec3 normalize(const vec3& v) {
		float len = length(v);
		return vec3(v.x/len, v.y/len, v.z/len);
	}
	vec4 normalize(const vec4& v) {
		float len = length(v);
		return vec4(v.x/len, v.y/len, v.z/len, v.w/len);
	}

	mat4 scale(const mat4& m, const vec3& vec) {
		mat4 m4;
		for (int i = 0; i < 4; i++) {
			m4.m[i][0] = m.m[i][0]*vec.x;
			m4.m[i][1] = m.m[i][1]*vec.y;
			m4.m[i][2] = m.m[i][2]*vec.z;
		}
		return m4;
	}

	float length(const vec2& vec){
		return (float)sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	float length(const vec3& vec){
		return (float)sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	float length(const vec4& vec){
		return (float)sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
	}

};
