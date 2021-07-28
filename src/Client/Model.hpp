#pragma once

#include "OBJLoader.hpp"
#include "Vertex.hpp"
#include <GL/glew.h>

class Model {
public:

	void init(const std::string& path);
	void render() const;
	void destroy();

private:

	GLuint m_numVertices = 0;
	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_eboID = 0;

};