#pragma once

#include <unordered_map>
#include <string>
#include <GL/glew.h>
#include "Math.hpp"
#include "ParticleTexture.hpp"

class ParticleTexture {
public:

	void loadFromFile(const std::string& path);
	void bind();
	void unbind();
	void destroy();
	math::vec4 getUVQuad(unsigned int _particleID);

private:

	GLuint m_textureID = 0;


};