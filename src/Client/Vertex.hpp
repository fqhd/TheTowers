#pragma once
#include <GL/glew.h>
#include "Math.hpp"
#include "ColorRGBA8.hpp"

struct ModelVertex {
	ModelVertex(const math::vec3& _position, const math::vec3& _normal, const math::vec2& _uv){
		position = _position;
		normal = _normal;
		uv = _uv;
	}
	math::vec3 position;
	math::vec3 normal;
	math::vec2 uv;
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
