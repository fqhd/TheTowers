#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <cstddef>
#include "../Utils/Vertex.hpp"
#include <iostream>
#include <SFML/Network.hpp>

const unsigned int CHUNK_WIDTH = 32;
const unsigned int CHUNK_SIZE = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_WIDTH;

class Chunk {
public:

	Chunk();
	void init(int _x, int _y, int _z);

	// Utility functions
	void render();
	void destroy();
	void pushData(GLuint* vertices, unsigned int numVertices);
	unsigned int getNumVertices();

	// Public variables
	int x = 0;
	int y = 0;
	int z = 0;
	bool needsMeshUpdate = true;

private:

	// Opengl Variables
	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_numVertices = 0;

};

