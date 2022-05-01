#pragma once

#include <iostream>
#include <glad.h>

class FaceOutline {
public:

	void init();
	void render(unsigned int faceIndex, unsigned int numFaces) const;
	void destroy();

private:

	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_eboID = 0;

};