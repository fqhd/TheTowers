#ifndef CHUNK_H
#define CHUNK_H
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
	void pushData(GLuint* vertices, unsigned int numVertices);
	unsigned int getNumVertices();

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
