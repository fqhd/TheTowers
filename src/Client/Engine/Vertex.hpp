#pragma once

#include <GLAD/glad.h>
#include <glm/glm.hpp>
#include "ColorRGBA8.hpp"

struct ModelVertex {
	ModelVertex(const glm::vec3& _position, const glm::vec3& _normal){
		position = _position;
		normal = _normal;
	}
	glm::vec3 position;
	glm::vec3 normal;
};

struct GUITextVertex {
	GUITextVertex(const glm::vec2& p, const glm::vec2& u){
		position = p;
		uv = u;
	}
	glm::vec2 position;
	glm::vec2 uv;
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
	ItemVertex(const glm::vec2& _pos, unsigned int _uv){
		position = _pos;
		uv = _uv;
	}
	glm::vec2 position;
	unsigned int uv;
};
