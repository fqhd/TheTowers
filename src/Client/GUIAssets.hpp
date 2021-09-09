#pragma once

#include <GL/glew.h>
#include <unordered_map>
#include "Image.hpp"
#include <string>

class GUIAssets {
public:

	// Asks for the name of the texture(NOT THE PATH AND WITHOUT THE .PNG EXTENSION)
	// This function looks for textures in the "res/textures/gui/" directory
	static GLuint getTexture(const std::string& _name); 

	// Deletes all the textures from the graphics card
	static void destroy();

private:

	static std::unordered_map<std::string, GLuint> m_textureMap;


};
