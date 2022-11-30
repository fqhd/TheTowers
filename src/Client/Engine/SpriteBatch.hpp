#pragma once

#include <GLAD/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include "Vertex.hpp"

class SpriteBatch {
public:

	void init(GLuint textureID);
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, const ColorRGBA8& color); // Adds sprite to draw call
	void batch(); // Batches all the sprites together(sends them to the GPU under one vao)
	void render(); // Renders the sprites
	void destroy();

private:

	GLuint m_vbo;
	GLuint m_vao;
	GLuint m_textureID;
	GLuint m_vertexCount;

	std::vector<GUIVertex> m_vertices;
};
