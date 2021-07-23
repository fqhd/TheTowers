#define STB_TRUETYPE_IMPLEMENTATION

#include "SpriteFont.hpp"
#include "../Utils/Utils.hpp"

void SpriteFont::init(const std::string& fontLocation, float pixelHeight, unsigned int w, unsigned int h, unsigned int firstChar, unsigned int numChars) {
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

void SpriteFont::bindTexture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void SpriteFont::unbindTexture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SpriteFont::destroy() {
	free(m_charData);
	glDeleteTextures(1, &m_textureID);
}

void flipQuad(math::vec4& quad, float baseline){
	float diff = baseline - (quad.y + quad.w);
	quad.y = baseline + diff;
}

void SpriteFont::printFont(SpriteBatch& _batch, const std::string& s, const math::vec2& position, const math::vec2& scale, const ColorRGBA8& color) {
	float xPos = position.x;
	float yPos = position.y;

	for (unsigned int i = 0; i < s.size(); i++) {
		stbtt_aligned_quad q;

		stbtt_GetBakedQuad(m_charData, m_bitmapWidth, m_bitmapHeight, s[i] - 32, &xPos, &yPos, &q, scale.x, 1);

		float x = q.x0;
		float y = q.y0;
		float w = (q.x1 - q.x0);
		float h = (q.y1 - q.y0);
		math::vec4 quad = math::vec4(x, y, w, h);
		flipQuad(quad, yPos);

		quad.z *= scale.x;
		quad.w *= scale.y;

		_batch.draw(quad, math::vec4(q.s0, q.t0 + (q.t1 - q.t0), q.s1 - q.s0, -(q.t1 - q.t0)), m_textureID, color);
	}
}

