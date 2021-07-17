#pragma once

#include "SpriteBatch.hpp"
#include "SpriteShader.hpp"

class GUIRenderer {

	void init();
	void begin();
	void drawRect();
	void end();
	void render();

private:

	SpriteBatch m_guiBatch;
	SpriteShader m_guiShader;

};