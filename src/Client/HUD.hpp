#pragma once

#include "Engine/GUI/GUIImageRenderer.hpp"

class HUD {
public:

	void init();
	void render();
	void destroy();

private:

	void addTextures();
	void addImages();

	GUIImageRenderer m_imageRenderer;

};