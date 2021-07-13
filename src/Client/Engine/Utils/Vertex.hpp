#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ColorRGBA8.hpp"


struct GUIImageVertex {
	GUIImageVertex(const glm::vec2& _p, GLubyte _uv){
		position = _p;
		uv = _uv;
	}
	glm::vec2 position;
	GLubyte uv = 0;
};

struct GUITextVertex {
	GUITextVertex(const glm::vec2& p, const glm::vec2& u){
		position = p;
		uv = u;
	}
	glm::vec2 position;
	glm::vec2 uv;
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
