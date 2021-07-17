#pragma once

#include <GL/glew.h>

enum Face {
	FACE_0,
	FACE_1,
	FACE_2,
	FACE_3,
	FACE_4,
	FACE_5,
};

class OutlineRenderer {
public:

	void init();
	void renderFace(Face face);
	void destroy();


private:

	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_eboID = 0;

};


