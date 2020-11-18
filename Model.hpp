#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Transform.hpp"
#include "OBJLoader.hpp"


class Model {
public:

	Model(const Transform& t, const char* path);
	void render();
	void destroy();



	Transform transform;

private:

	GLuint m_numVertices = 0;
	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_eboID = 0;


};