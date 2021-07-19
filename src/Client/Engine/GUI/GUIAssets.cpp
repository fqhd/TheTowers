#include "GUIAssets.hpp"

void GUIAssets::init(){
	m_crosshair = loadTexture("res/textures/gui/crosshair.png");
	m_hotbar = loadTexture("res/textures/gui/hotbar.png");
	m_selector = loadTexture("res/textures/gui/selector.png");
	m_blank = loadTexture("res/textures/gui/blank.png");
	m_grass = loadTexture("res/textures/gui/grass.png");
}

void GUIAssets::destroy(){
	glDeleteTextures(1, &m_crosshair);
	glDeleteTextures(1, &m_hotbar);
	glDeleteTextures(1, &m_selector);
	glDeleteTextures(1, &m_blank);
}

GLuint GUIAssets::loadTexture(const std::string& _path){
	Image image;
	image.loadFromFile(_path);

	GLuint tID;
	glGenTextures(1, &tID);
	glBindTexture(GL_TEXTURE_2D, tID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());

	glBindTexture(GL_TEXTURE_2D, 0);

	image.free();

	return tID;
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

GLuint GUIAssets::getGrassTexture(){
	return m_grass;
}
