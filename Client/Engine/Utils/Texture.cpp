#include "Texture.hpp"

void Texture::init(const char* path) {
	
	Image image;
	image.loadFromFile("res/textureMap");
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
	
	// Upload data to GPU
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, image.getWidth(), image.getHeight(), 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	// Free memory from RAM
	image.free();

}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void Texture::destroy() {
	glDeleteTextures(1, &textureID);
}