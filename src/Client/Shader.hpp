#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include "Math.hpp"

class Shader {
public:

	void loadShader(const char* vs, const char* fs);
	void bind();
	void unbind();
	void destroy();

	void loadUniform(const const std::string& name, const math::vec3& vec);
	void loadUniform(const const std::string& name, const math::mat4& matrix);
	void loadUniform(const const std::string& name, float f);
	void loadUniform(const const std::string& name, int i);
	void loadUniform(const const std::string& name, bool b);

private:

	GLint getUniformLocation(const std::string& name);

	std::unordered_map<std::string, GLint> m_uniformLocations;

	GLuint m_programID = 0;
	GLuint m_vertexID = 0;
	GLuint m_fragmentID = 0;

};


