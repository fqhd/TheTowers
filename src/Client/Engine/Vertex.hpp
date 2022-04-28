#pragma once
#include <glad.h>
#include "Math.hpp"
#include "ColorRGBA8.hpp"

struct ModelVertex {
	ModelVertex(const math::vec3& _position, const math::vec3& _normal){
		position = _position;
		normal = _normal;
	}
	math::vec3 position;
	math::vec3 normal;
};

struct GUITextVertex {
	GUITextVertex(const math::vec2& p, const math::vec2& u){
		position = p;
		uv = u;
	}
	math::vec2 position;
	math::vec2 uv;
};

struct GUIVertex {
	GUIVertex(){
		x = 0.0f;
		y = 0.0f;
		u = 0.0f;
		v = 0.0f;
	}
	GUIVertex(float _x, float _y, float _u, float _v, const ColorRGBA8& _color){
		x = _x;
		y = _y;
		u = _u;
		v = _v;
		color = _color;
	}
	float x;
	float y;
	float u;
	float v;
	ColorRGBA8 color;
};

struct ItemVertex {
	ItemVertex(const math::vec2& _pos, unsigned int _uv){
		position = _pos;
		uv = _uv;
	}
	math::vec2 position;
	unsigned int uv;
};
