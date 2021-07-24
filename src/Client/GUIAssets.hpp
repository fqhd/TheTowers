#pragma once

#include <GL/glew.h>
#include "Image.hpp"

class GUIAssets {
public:

	void init();
	void destroy();

	GLuint getCrosshairTexture();
	GLuint getHotbarTexture();
	GLuint getSelectorTexture();
	GLuint getBlankTexture();
	GLuint getGrassTexture();

private:

	GLuint loadTexture(const std::string& _path);

	GLuint m_crosshair = 0;
	GLuint m_hotbar = 0;
	GLuint m_selector = 0;
	GLuint m_blank = 0;
	GLuint m_grass = 0;
	




};