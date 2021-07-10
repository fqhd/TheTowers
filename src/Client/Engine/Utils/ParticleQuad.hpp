#pragma once

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include "Vertex.hpp"

class ParticleQuad {
public:

	void init();
	void bind();
	void unbind();
	void render();
	void destroy();

	void pushMatrices(const std::vector<glm::mat4>& matrices);



private:

	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_ivboID = 0;
	GLuint m_colorsVBOID = 0;


};

#endif
