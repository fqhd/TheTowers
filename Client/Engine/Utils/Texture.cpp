#include "Texture.hpp"

void Texture::init(const char* path) {
	
	Image image;
	image.loadFromFile(path);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);

	// Upload data to GPU

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, image.getWidth(), image.getWidth(), 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());

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