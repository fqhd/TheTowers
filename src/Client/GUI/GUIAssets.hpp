#pragma once

#include <glad.h>
#include <unordered_map>
#include "Image.hpp"
#include <string>

namespace GUIAssets {

	// Asks for the name of the texture(NOT THE PATH AND WITHOUT THE .PNG EXTENSION)
	// This function looks for textures in the "res/textures/gui/" directory
	GLuint getTexture(const std::string& _name); 

	// Deletes all the textures from the graphics card
	void destroy();



};
