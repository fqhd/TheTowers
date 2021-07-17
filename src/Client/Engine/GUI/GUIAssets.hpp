#pragma once

class GUIAssets {
public:

	void init();
	void destroy();

	GLuint getCrosshair();
	GLuint getHotbar();
	GLuint getSelector();
	GLuint getBlank();

private:

	GLuint loadTexture(const std::string& path);

	GLuint m_crosshair = 0;
	GLuint m_hotbar = 0;
	GLuint m_selector = 0;
	GLuint m_blank = 0;
	




};