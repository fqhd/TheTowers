#pragma once

#include <string>
#include "stb_truetype.h"
#include "SpriteBatch.hpp"


class SpriteFont {
public:

	void init(const std::string& fontLocation, float pixelHeight, unsigned int w, unsigned int h, unsigned int firstChar = 32, unsigned int numChars = 95);
	void printFont(SpriteBatch& _batch, const std::string& s, const glm::vec2& position, const glm::vec2& scale, const ColorRGBA8& color);
	GLuint getTextureID() const;
	void destroy();


private:

	unsigned int m_bitmapWidth = 0;
	unsigned int m_bitmapHeight = 0;
	stbtt_bakedchar* m_charData = nullptr;
	GLuint m_textureID = 0;

};
