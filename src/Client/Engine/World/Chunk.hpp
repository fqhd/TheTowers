#ifndef CHUNK_H
#define CHUNK_H
#include <glm/glm.hpp>
#include <vector>
#include <cstddef>
#include "../Utils/Vertex.hpp"
#include <iostream>

const unsigned int CHUNK_WIDTH = 32;
const unsigned int CHUNK_SIZE = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_WIDTH;

class Chunk {
public:

	Chunk();
	void init(int _x, int _y, int _z, uint8_t* _dataptr);

	// Utility functions
	void render();
	void destroy();
	void pushData(GLuint* vertices, unsigned int numVertices);
	unsigned int getNumVertices();
	uint8_t getBlock(uint8_t _x, uint8_t _y, uint8_t _z);
	void setBlock(uint8_t _x, uint8_t _y, uint8_t _z, uint8_t _blockID);

	// Public variables
	int x = 0;
	int y = 0;
	int z = 0;
	bool needsUpdate = true;

private:

	uint8_t* m_data = nullptr;

	// Opengl Variables
	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_numVertices = 0;

};

#endif
