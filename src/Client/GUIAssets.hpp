#pragma once

#include <epoxy/gl.h>
#include <unordered_map>
#include "Image.hpp"
#include "ItemTexture.hpp"
#include <string>

class GUIAssets {
public:

	void init();
	GLuint getTexture(const std::string& _name);
	const ItemTexture& getItemTexture();
	void destroy();

private:

	ItemTexture m_itemTexture;
	std::unordered_map<std::string, GLuint> m_textureMap;


};
