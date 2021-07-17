#include "GUIAssets.hpp"

void GUIAssets::init(){
	m_crosshair = loadTexture("res/textures/crosshair.png");
	m_hotbar = loadTexture("res/textures/hotbar.png");
	m_selector = loadTexture("res/textures/selector.png");
	m_blank = loadTexture("res/textures/blank.png");
}

void GUIAssets::destroy(){
	glDeleteTextures(1, &m_textureID);
}

GLuint GUIAssets::loadTexture(const std::string& path){

}


// Texture Getters

GLuint GUIAssets::getCrosshairTexture(){
	return m_crosshair;
}

GLuint GUIAssets::getHotbarTexture(){
	return m_hotbar;
}

GLuint GUIAssets::getSelectorTexture(){
	return m_selector;
}

GLuint GUIAssets::getBlankTexture(){
	return m_blank;
}
