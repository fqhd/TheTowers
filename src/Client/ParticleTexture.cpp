#include "ParticleTexture.hpp"
#include "Image.hpp"

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

math::vec4 ParticleTexture::getUVQuad(unsigned int _particleID){
	return math::vec4(0, 0, 1, 1);
}