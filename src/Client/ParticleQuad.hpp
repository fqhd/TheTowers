#pragma once

#include <GL/glew.h>
#include <vector>
#include "Vertex.hpp"

struct ParticleInstance {
	ParticleInstance(){}
	ParticleInstance(const math::vec3& p, unsigned int i){
		pos = p;
		tindex = i;
	}
	math::vec3 pos;
	unsigned int tindex;
};

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


