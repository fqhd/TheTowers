#pragma once

#include <GL/glew.h>

class Cube {
public:

	void init();
	void render(unsigned int numFaces, unsigned int face) const;
	void destroy();

private:

	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_eboID = 0;

};


