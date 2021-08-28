#pragma once

#include <iostream>
#include <GL/glew.h>

class Outline {
public:

	void init();
	void render(unsigned int faceIndex, unsigned int numFaces) const;
	void destroy();

private:

	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_eboID = 0;

};


