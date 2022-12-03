#pragma once

#include <vector>
#include <cstddef>
#include "Vertex.hpp"
#include <iostream>

class Chunk {
public:

	Chunk();
	void init(int _x, int _y, int _z);

	// Utility functions
	void render();
	void pushData();
	unsigned int getNumVertices();
	void destroy();

	// Public variables
	int x = 0;
	int y = 0;
	int z = 0;
	std::vector<GLuint> vertices;
	bool needsMeshUpdate = true;
	bool needsVaoUpdate = false;

private:

	// Opengl Variables
	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_numVertices = 0;

};

