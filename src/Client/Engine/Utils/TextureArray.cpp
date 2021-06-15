#include "TextureArray.hpp"

void TextureArray::init(const char* _path, unsigned int _numLayers) {
	
	Image image;
	image.loadFromFile(_path);
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);

	// Upload data to GPU
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, image.getWidth(), image.getWidth(), _numLayers, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());
	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	// Free memory from RAM
	image.free();

}

void TextureArray::bind() {
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
}

void TextureArray::unbind() {
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void TextureArray::destroy() {
	glDeleteTextures(1, &textureID);
}