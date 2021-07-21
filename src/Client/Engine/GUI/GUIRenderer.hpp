#pragma once

#include "SpriteBatch.hpp"
#include "SpriteShader.hpp"
#include "SpriteFont.hpp"
#include "GUIAssets.hpp"

class GUIRenderer {
public:

	void init(unsigned int windowWidth, unsigned int windowHeight);
	void begin();
	void drawRect(const math::vec4& destRect, const math::vec4& uvRect, GLuint texture, const ColorRGBA8& color);
	void drawText(const std::string& s, const math::vec2& position, const ColorRGBA8& color);
	void end();
	void render();
	void destroy();

	GUIAssets assets;

private:

	SpriteBatch m_guiBatch;
	SpriteBatch m_textBatch;
	SpriteFont m_spriteFont;
	SpriteShader m_guiShader;


};
