#pragma once

#include <GL/glew.h>
#include <unordered_map>
#include "Image.hpp"
#include <string>

class GUIAssets {
public:

	GLuint getTexture(const std::string& _name);
	void destroy();

private:

	std::unordered_map<std::string, GLuint> m_textureMap;


};
