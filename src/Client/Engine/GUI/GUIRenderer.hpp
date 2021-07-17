#pragma once

#include "SpriteBatch.hpp"
#include "SpriteShader.hpp"
#include "SpriteFont.hpp"

class GUIRenderer {

	void init();
	void begin();
	void drawRect(const math::vec4& destRect, const math::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color);
	void drawText(const std::string& s, const math::vec2& position, const ColorRGBA8& color);
	void end();
	void render();

private:

	SpriteBatch m_guiBatch;
	SpriteBatch m_textBatch;
	SpriteFont m_spriteFont;
	SpriteShader m_guiShader;


};