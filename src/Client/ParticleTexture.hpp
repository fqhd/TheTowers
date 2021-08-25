#pragma once

#include <unordered_map>
#include <string>
#include <epoxy/gl.h>
#include "Math.hpp"
#include "ParticleTexture.hpp"
#include "ParticleID.hpp"

const unsigned int NUM_PARTICLE_UVS = 128;

class ParticleTexture {
public:

	void loadFromFile(const std::string& path);
	void bind();
	void unbind();
	void destroy();
	const math::vec4& getUVQuad(ParticleID _particleID) const;

private:

	void populateUVQuadsArray();
	math::vec4 m_uvQuads[NUM_PARTICLE_UVS];
	GLuint m_textureID = 0;

};
