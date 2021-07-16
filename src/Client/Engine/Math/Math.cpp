#include "Math.hpp"
#include <cmath>
#include <string>

#include "Mat4.hpp"

namespace math {

	mat4 view(const vec3& position, float pitch, float yaw){
        vec3 side(1,0,0);
        vec3 up(0,1,0);

		mat4 p;
		mat4 y;
		mat4 v;
		p.setIdentity();
		y.setIdentity();
		v.setIdentity();
        rotate(toRadians(pitch), side, p, v);
        rotate(toRadians(yaw), up, y, v);
        translate(-position, v, v);
		return v;
	}

	float dot(const vec3& a, const vec3& b){
		return a.x * b.x + a.y * b.y * a.z * b.z;
	}

	void rotate(float angle, const vec3& axis, const mat4& src, mat4& dst){
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

		float t00 = src.m[0][0] * f00 + src.m[1][0] * f01 + src.m[2][0] * f02;
		float t01 = src.m[0][1] * f00 + src.m[1][1] * f01 + src.m[2][1] * f02;
		float t02 = src.m[0][2] * f00 + src.m[1][2] * f01 + src.m[2][2] * f02;
		float t03 = src.m[0][3] * f00 + src.m[1][3] * f01 + src.m[2][3] * f02;
		float t10 = src.m[0][0] * f10 + src.m[1][0] * f11 + src.m[2][0] * f12;
		float t11 = src.m[0][1] * f10 + src.m[1][1] * f11 + src.m[2][1] * f12;
		float t12 = src.m[0][2] * f10 + src.m[1][2] * f11 + src.m[2][2] * f12;
		float t13 = src.m[0][3] * f10 + src.m[1][3] * f11 + src.m[2][3] * f12;

		dst.m[2][0] = src.m[0][0] * f20 + src.m[1][0] * f21 + src.m[2][0] * f22;
		dst.m[2][1] = src.m[0][1] * f20 + src.m[1][1] * f21 + src.m[2][1] * f22;
		dst.m[2][2] = src.m[0][2] * f20 + src.m[1][2] * f21 + src.m[2][2] * f22;
		dst.m[2][3] = src.m[0][3] * f20 + src.m[1][3] * f21 + src.m[2][3] * f22;
		dst.m[0][0] = t00;
		dst.m[0][1] = t01;
		dst.m[0][2] = t02;
		dst.m[0][3] = t03;
		dst.m[1][0] = t10;
		dst.m[1][1] = t11;
		dst.m[1][2] = t12;
		dst.m[1][3] = t13;
	}

	vec3 cross(const vec3& a, const vec3& b){
		vec3 r;
		r.x = a.y * b.z - a.z * b.y;
		r.y = b.x * a.z - b.z * a.x;
		r.z = a.x * b.y - a.y * b.x;
		return r;
	}

	void translate(const vec3& vec, const mat4& src, mat4& dst) {
		dst.m[3][0] += src.m[0][0] * vec.x + src.m[1][0] * vec.y + src.m[2][0] * vec.z;
		dst.m[3][1] += src.m[0][1] * vec.x + src.m[1][1] * vec.y + src.m[2][1] * vec.z;
		dst.m[3][2] += src.m[0][2] * vec.x + src.m[1][2] * vec.y + src.m[2][2] * vec.z;
		dst.m[3][3] += src.m[0][3] * vec.x + src.m[1][3] * vec.y + src.m[2][3] * vec.z;
	}

	mat4 perspective(float fov, float aspect, float zNear, float zFar) {
		float scale = 1 / tan(fov * 0.5 * M_PI / 180);
		mat4 r;
		r.m[0][0] = scale; // scale the x coordinates of the projected point
		r.m[1][1] = scale; // scale the y coordinates of the projected point
		r.m[2][2] = -zFar / (zFar - zNear); // used to remap z to [0,1]
		r.m[3][2] = -zFar * zNear / (zFar - zNear); // used to remap z [0,1]
		r.m[2][3] = -1; // set w = -z
		r.m[3][3] = 0;
		return r;
	}

	mat4 ortho(float left, float right, float bottom, float top) {
		mat4 Result;
		Result.m[0][0] = 2 / (right - left);
		Result.m[1][1] = 2 / (top - bottom);
		Result.m[3][0] = - (right + left) / (right - left);
		Result.m[3][1] = - (top + bottom) / (top - bottom);
		Result.m[3][3] = 1;
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

	void scale(const vec3& vec, const mat4& src, mat4& dst) {
		for (int i = 0; i < 4; i++) {
			dst.m[i][0] = src.m[i][0]*vec.x;
			dst.m[i][1] = src.m[i][1]*vec.y;
			dst.m[i][2] = src.m[i][2]*vec.z;
		}
	}

	float fabs(float v){
		if(v < 0){
			return -v;
		}
		return v;
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
