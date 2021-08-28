#pragma once

#include <GL/glew.h>
#include <vector>
#include "Vertex.hpp"


class ParticleQuad {
public:

	void init();
	void render(unsigned int _numInstances);
	void destroy();

	void pushMatrices(const std::vector<math::mat4>& _matrices);
	void pushUVQuads(const std::vector<math::vec4>& _uvs);

private:

	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_mvboID = 0; // Matrices buffer
	GLuint m_uvboID = 0; // UVs buffer


};


