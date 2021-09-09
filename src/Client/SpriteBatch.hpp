#pragma once

#include <GL/glew.h>
#include <vector>
#include "Math.hpp"
#include "Vertex.hpp"


class Glyph {
public:
	Glyph() {};
	Glyph(const math::vec4& destRect, const math::vec4& uvRect, const ColorRGBA8& color);

	GUIVertex topLeft;
	GUIVertex bottomLeft;
	GUIVertex topRight;
	GUIVertex bottomRight;
};

class SpriteBatch {
public:

	void init(GLuint textureID);
	void draw(const math::vec4& destRect, const math::vec4& uvRect, const ColorRGBA8& color); // Adds sprite to draw call
	void batch(); // Batches all the sprites together(sends them to the GPU under one vao)
	void render(); // Renders the sprites
	void destroy();

private:

	GLuint m_vbo;
	GLuint m_vao;
	GLuint m_textureID;

	std::vector<Glyph> m_glyphs;
};
