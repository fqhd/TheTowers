#ifndef VERTEX_H
#define VERTEX_H

#include "../Libs/glad.h"
#include <glm/glm.hpp>

struct vec3 {
	vec3(){}
	vec3(GLubyte red, GLubyte green, GLubyte blue){
		r = red;
		g = green;
		b = blue;
	}
	GLubyte r = 0;
	GLubyte g = 0;
	GLubyte b = 0;
};

struct vec2 {
	vec2(){}
	vec2(GLubyte u, GLubyte v){
		x = u;
		y = v;
	}
	GLubyte x = 0;
	GLubyte y = 0;
};

struct ColorRGBA8 {
	ColorRGBA8() : r(255), g(255), b(255), a(255) { }
	ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) :
		r(R), g(G), b(B), a(A) { }
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct ModelVertex {
	ModelVertex(const glm::vec3& p, const glm::vec3& n){
		position = p;
		normal = n;
	}
	glm::vec3 position;
	glm::vec3 normal;
};

struct Vertex {
	Vertex(const glm::vec3& _position, const vec3& _color){
		position = _position;
		color = _color;
	}
	glm::vec3 position;
	vec3 color;
};

struct GUIVertex{
	GUIVertex(const glm::vec2& p, const ColorRGBA8& c){
		position = p;
		color = c;
	}
	glm::vec2 position;
	ColorRGBA8 color;
};

#endif
