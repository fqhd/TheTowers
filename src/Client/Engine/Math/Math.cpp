#include "Math.hpp"
#include <cmath>
#include <string>

#include "Mat4.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace math {

	mat4 view(const vec3& position, const vec3& forward){
		glm::vec3 p = glm::vec3(position.x, position.y, position.z);
		glm::vec3 f = glm::vec3(forward.x, forward.y, forward.z);

		glm::mat4 glmView = glm::lookAt(p, p + f, glm::vec3(0, 1, 0));

		mat4 view;
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				view.m[i][j] = glmView[i][j];
			}
		}
		return view;
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
		float tanHalfFovy = tan(fov / 2);
		mat4 Result(0);
		Result.m[0][0] = 1 / (aspect * tanHalfFovy);
		Result.m[1][1] = 1 / (tanHalfFovy);
		Result.m[2][2] = - (zFar + zNear) / (zFar - zNear);
		Result.m[2][3] = - 1;
		Result.m[3][2] = - (2 * zFar * zNear) / (zFar - zNear);
		return Result;
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
