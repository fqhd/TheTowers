#pragma once

#include "Image.hpp"


struct TextureArray {

	TextureArray(){}

	void init(const std::string& path, unsigned int _numLayers);
	void bind();
	void unbind();
	void destroy();

	GLuint textureID = 0;

};

