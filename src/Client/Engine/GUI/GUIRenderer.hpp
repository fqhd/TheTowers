#pragma once

#include <vector>
#include <GL/glew.h>
#include "../Utils/Vertex.hpp"
#include "../Utils/Utils.hpp"

class GUIRenderer {
public:

	void init();
	void begin();
	void draw(const math::vec4& destRect, const ColorRGBA8& color, unsigned int layer);
	void end();
	void render();

	void destroy();

private:

	void uploadData();

	GLuint m_vbo = 0;
	GLuint m_vao = 0;

	std::vector<GUIVertex> m_vertices;

};
