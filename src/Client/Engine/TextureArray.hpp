#pragma once

#include <glad.h>
#include "Image.hpp"


struct TextureArray {

	TextureArray(){}

	void init(const char* _path, unsigned int _numLayers);
	void bind();
	void unbind();
	void destroy();

	GLuint textureID = 0;

};

