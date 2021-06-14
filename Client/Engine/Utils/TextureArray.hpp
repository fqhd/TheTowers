#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include "Image.hpp"


struct TextureArray {

	TextureArray(){}

	void init(const char* path);
	void bind();
	void unbind();
	void destroy();

	GLuint textureID = 0;

};

#endif