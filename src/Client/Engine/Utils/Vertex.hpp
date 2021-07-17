#pragma once
#include <GL/glew.h>
#include "../Math/Math.hpp"
#include "ColorRGBA8.hpp"

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
	GUIVertex(const math::vec3& _position, const ColorRGBA8& _color, const math::vec2& _uv){
		position = _position;
		color = _color;
		uv = _uv;
	}
	void setPosition(float x, float y, float z){
		position.x = x;
		position.y = y;
		position.z = z;
	}
	void setUV(float u, float v){
		uv.x = u;
		uv.y = v;
	}
	math::vec3 position;
	math::vec2 uv;
	ColorRGBA8 color;
};
