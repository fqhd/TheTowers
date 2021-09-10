#pragma once

#include "SpriteBatch.hpp"
#include "Shader.hpp"
#include "SpriteFont.hpp"
#include "Utils.hpp"

namespace GUIRenderer {

	void init(unsigned int windowWidth, unsigned int windowHeight, GLuint textureID);
	void drawRect(const math::vec4& destRect, const math::vec4& uvRect, const ColorRGBA8& color);
	void drawText(const std::string& s, const math::vec2& position, const math::vec2& scale, const ColorRGBA8& color);
	void batch();
	void render();
	void destroy();


};
