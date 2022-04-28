#pragma once

#include <glad.h>

class LegacyOutline {
public:

	void init();
	void render();
	void destroy();

private:

	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;

};