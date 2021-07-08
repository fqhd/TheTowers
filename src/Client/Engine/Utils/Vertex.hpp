#ifndef VERTEX_H
#define VERTEX_H

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

struct ModelVertex {
	ModelVertex(const glm::vec3& p, const glm::vec3& n){
		position = p;
		normal = n;
	}
	glm::vec3 position;
	glm::vec3 normal;
};

struct GUIVertex {
	GUIVertex(const glm::vec2& p, const ColorRGBA8& c){
		position = p;
		color = c;
	}
	glm::vec2 position;
	ColorRGBA8 color;
};

#endif
