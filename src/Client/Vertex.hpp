#pragma once
#include <GL/glew.h>
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
	GUIVertex(){}
	GUIVertex(const math::vec2& _position, const ColorRGBA8& _color, const math::vec2& _uv){
		position = _position;
		color = _color;
		uv = _uv;
	}
	void setPosition(float x, float y){
		position.x = x;
		position.y = y;
	}
	void setUV(float u, float v){
		uv.x = u;
		uv.y = v;
	}
	math::vec2 position;
	math::vec2 uv;
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
