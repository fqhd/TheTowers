#pragma once

#include <vector>
#include "GUICanvas.hpp"

class GUIHandler {
public:

	void init(GUIFont* _font, TextureArray* _textureArray);
	void destroy();

	GUICanvas* createCanvas();

	GUIRenderer guiRenderer;
	GUIShader guiShader;

private:

	void renderGUI();
	void renderFonts();

	std::vector<GUICanvas*> m_canvases;
	GUIFont* m_font = nullptr;
	TextureArray* m_textureArray = nullptr;
	GUIFontShader m_fontShader;


};
