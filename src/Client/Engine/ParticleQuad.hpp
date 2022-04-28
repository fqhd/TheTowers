#pragma once

#include <glad.h>
#include <vector>
#include "Vertex.hpp"

class ParticleQuad {
public:

	void init();
	void render(unsigned int _numInstances);
	void destroy();

	void pushData(const void* _data, unsigned int _size);

private:

	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;


};


