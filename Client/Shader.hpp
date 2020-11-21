#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>

class Shader{

public:

	void loadShader(const char* vs, const char* fs);
	void bind();
	void unbind();
	void destroy();

protected:

	GLuint m_programID;
	GLuint m_vertexID;
	GLuint m_fragmentID;
};