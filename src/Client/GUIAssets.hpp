#pragma once

#include <epoxy/gl.h>
#include <unordered_map>
#include "Image.hpp"
#include <string>

class GUIAssets {
public:

	void init();
	GLuint getTexture(const std::string& _name);
	void destroy();

private:

	std::unordered_map<std::string, GLuint> m_textureMap;


};
