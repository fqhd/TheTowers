#pragma once

#include <unordered_map>
#include <string>
#include <GL/glew.h>
#include "Math.hpp"
#include "ParticleTexture.hpp"
#include "ParticleID.hpp"

class ParticleTexture {
public:

	void loadFromFile(const std::string& path);
	void bind();
	void unbind();
	void destroy();
	const math::vec4& getUVQuad(ParticleID _particleID) const;

private:

	void populateUVQuadsArray();
	math::vec4 calcUVQuad(ParticleID _particleID);
	math::vec4 m_uvQuads[128];
	GLuint m_textureID = 0;

};