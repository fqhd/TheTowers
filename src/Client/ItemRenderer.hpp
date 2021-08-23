#pragma once

#include <GL/glew.h>
#include "Vertex.hpp"

class ItemRenderer {
public:

	void init(); // Creates the VAO and VBO
	void begin(); // Clears vertices on the RAM
	void draw(const math::vec2& _area, unsigned int _uv); // Adds an item with the _uvIndex to the list of vertices
	void end(); // Sends the vertices to the GPU(vertices which were created by the draw function)
	void render(); // Renders the vertices
	void destroy(); // Destroys the VAO and VBO

private:

	std::vector<ItemVertex> m_vertices;
	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;

};
