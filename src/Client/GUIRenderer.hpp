#pragma once

#include "SpriteBatch.hpp"
#include "Shader.hpp"
#include "SpriteFont.hpp"
#include "GUIAssets.hpp"
#include "Utils.hpp"

class GUIRenderer {
public:

	static void init(unsigned int windowWidth, unsigned int windowHeight, GLuint textureID);
	static void drawRect(const math::vec4& destRect, const math::vec4& uvRect, const ColorRGBA8& color);
	static void drawText(const std::string& s, const math::vec2& position, const math::vec2& scale, const ColorRGBA8& color);
	static void batch();
	static void render();
	static void destroy();

private:

	static SpriteBatch m_guiBatch;
	static SpriteBatch m_textBatch;
	static SpriteFont m_spriteFont;
	static Shader m_shader;


};
