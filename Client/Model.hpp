#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "OBJLoader.hpp"


class Model {
public:

	void init(const char* path);
	void render();
	void destroy();


private:

	GLuint m_numVertices = 0;
	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_eboID = 0;


};
