#pragma once

#include <glad.h>
#include <string>
#include <fstream>
#include <unordered_map>
#include "Math.hpp"

class Shader {
public:

	void load(const char* vs, const char* fs);
	void bind();
	void unbind();
	void destroy();

	void loadUniform(const std::string& name, const math::vec3& vec);
	void loadUniform(const std::string& name, const math::mat4& matrix);
	void loadUniform(const std::string& name, float f);
	void loadUniform(const std::string& name, int i);
	void loadUniform(const std::string& name, bool b);

private:

	GLint getUniformLocation(const std::string& name);

	std::unordered_map<std::string, GLint> m_uniformLocations;

	GLuint m_programID = 0;
	GLuint m_vertexID = 0;
	GLuint m_fragmentID = 0;

};


