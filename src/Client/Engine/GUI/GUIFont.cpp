#define STB_TRUETYPE_IMPLEMENTATION

#include "GUIFont.hpp"
#include "../Utils/Utils.hpp"

void GUIFont::init(const std::string& fontLocation, float pixelHeight, unsigned int w, unsigned int h, unsigned int firstChar, unsigned int numChars) {
	// Variables
	m_bitmapWidth = w;
	m_bitmapHeight = h;

	// Allocating data for font loading and bitmap
	unsigned char* fontData = Utils::readFileToBuffer(fontLocation);
	uint8_t* bitmapBuffer = (uint8_t*)malloc(m_bitmapWidth * m_bitmapHeight);

	//Creating the bitmap
	m_charData = (stbtt_bakedchar*)malloc(sizeof(stbtt_bakedchar) * numChars);
	stbtt_BakeFontBitmap(fontData, 0, pixelHeight, bitmapBuffer, m_bitmapWidth, m_bitmapHeight, firstChar, numChars, m_charData);

	//Storing the bitmap into a texture
	glGenTextures(1, & m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_bitmapWidth, m_bitmapHeight, 0, GL_RED, GL_UNSIGNED_BYTE, bitmapBuffer);

	glBindTexture(GL_TEXTURE_2D, 0);

	free(bitmapBuffer);
	Utils::freeBuffer(fontData);
}

void GUIFont::bindTexture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void GUIFont::unbindTexture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GUIFont::destroy() {
	free(m_charData);
	glDeleteTextures(1, &m_textureID);
}

void GUIFont::printFont(SpriteBatch& _batch, const std::string& s, const math::vec2& position, const ColorRGBA8& color) {
	float wh = 1080.0f;
	float xPos = 0.0f;
	float yPos = wh - 0.0f;

	for (unsigned int i = 0; i < s.size(); i++) {
		stbtt_aligned_quad q;

		stbtt_GetBakedQuad(m_charData, m_bitmapWidth, m_bitmapHeight, s[i] - 32, &xPos, &yPos, &q, 1);

		_batch.draw(math::vec4(position.x + q.x0, position.y + wh - q.y0, position.x + q.x1, position.y + wh - q.y1), math::vec4(q.s0, q.t0, q.s1, q.t1), m_textureID, 1.0f, color);
	}
}