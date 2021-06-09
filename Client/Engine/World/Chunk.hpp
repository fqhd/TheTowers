#ifndef CHUNK_H
#define CHUNK_H
#include "../Libs/glad.h"
#include <glm/glm.hpp>
#include <vector>
#include <cstddef>
#include "../Utils/Vertex.hpp"


class Chunk {
public:

	Chunk();
	void init(int x, int y, int z);

	void render();
	void destroy();
	void pushData(Vertex* vertices, unsigned int numVertices);

	int x = 0;
	int y = 0;
	int z = 0;

	bool needsUpdate = true;

private:

	//Opengl Variables
	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_numVertices = 0;

};

#endif
