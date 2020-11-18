#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <cstddef>
#include <SFML/Graphics.hpp>
#include "Vertex.hpp"

class Chunk {
public:

	void init(unsigned int x, unsigned int z);

	void render();
	void destroy();
	void pushData(const std::vector<Vertex>& vertices);

	unsigned int getX();
	unsigned int getZ();

	bool needsUpdate = true;

private:

	//Opengl Variables
	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_numVertices = 0;
	unsigned int m_x = 0;
	unsigned int m_z = 0;

};
