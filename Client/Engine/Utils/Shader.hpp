#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <fstream>

class Shader {
public:

	void bind();
	void unbind();
	void destroy();


protected:

	void loadShader(const char* vs, const char* fs);
	GLuint m_programID = 0;
	GLuint m_vertexID = 0;
	GLuint m_fragmentID = 0;

};

#endif
