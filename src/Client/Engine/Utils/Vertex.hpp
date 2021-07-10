#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ColorRGBA8.hpp"

struct vec2 {
	vec2(){}
	vec2(GLubyte u, GLubyte v){
		x = u;
		y = v;
	}
	GLubyte x = 0;
	GLubyte y = 0;
};

struct QuadVertex {
	QuadVertex(const glm::vec2& _pos){
		position = _pos;
	}
	glm::vec2 position;
};

struct ModelVertex {
	ModelVertex(const glm::vec3& p, const glm::vec3& n){
		position = p;
		normal = n;
	}
	glm::vec3 position;
	glm::vec3 normal;
};

struct GUIVertex {
	GUIVertex(const glm::vec2& p, const ColorRGBA8& c, const glm::vec2& tInfo){
		position = p;
		color = c;
		textureInfo = tInfo;
	}
	glm::vec2 position;
	ColorRGBA8 color;
	glm::vec2 textureInfo;
};
