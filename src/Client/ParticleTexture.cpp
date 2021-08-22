#include "ParticleTexture.hpp"
#include "Image.hpp"

const unsigned int IMG_WIDTH = 160; // Width of the image texture
const unsigned int PARTICLE_WIDTH = 4; // Width of each individual particle

void ParticleTexture::loadFromFile(const std::string& path){
	// Creating the texture
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Loading the image data from the file and loading it to the GPU(generated texture)
	Image image;
	image.loadFromFile(path);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());
	image.free();
	glBindTexture(GL_TEXTURE_2D, 0);

	populateUVQuadsArray();
}

void ParticleTexture::populateUVQuadsArray(){
	for(unsigned int i = 0; i < 128; i++){
		m_uvQuads[i] = calcUVQuad((ParticleID)i);
	}
}

void ParticleTexture::bind(){
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void ParticleTexture::unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ParticleTexture::destroy(){
	glDeleteTextures(1, &m_textureID);
}

const math::vec4& ParticleTexture::getUVQuad(ParticleID _particleID) const {
	return m_uvQuads[(uint8_t)_particleID];
}

math::vec4 ParticleTexture::calcUVQuad(ParticleID _particleID) {
	uint8_t offset = (uint8_t)_particleID * PARTICLE_WIDTH;
	return math::vec4(1 + (uint8_t)_particleID + offset, 1 + offset/IMG_WIDTH, 4, 4) / IMG_WIDTH;
}
