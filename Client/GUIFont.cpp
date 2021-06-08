#define STB_TRUETYPE_IMPLEMENTATION

#include "GUIFont.hpp"
#include "Utils.hpp"
#include "Constants.hpp"

GUIFont::GUIFont(const std::string& fontLocation, float pixelHeight, unsigned int w, unsigned int h, unsigned int firstChar, unsigned int numChars) {

	// Variables
	m_bitmapWidth = w;
	m_bitmapHeight = h;

	// Allocating data for font loading and bitmap
	unsigned char * fontData = Utils::readFileToBuffer(fontLocation);
	uint8_t * bitmapBuffer = (uint8_t*) malloc(m_bitmapWidth * m_bitmapHeight);

	//Creating the bitmap
	m_charData = (stbtt_bakedchar*) malloc(sizeof(stbtt_bakedchar) * numChars);
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
	glDeleteTextures(1, & m_textureID);
}

void GUIFont::updateMesh(GUITextMesh& mesh) {
	//Going to take the mesh, create a set of vertices based on its string and upload the vertices to the meshes VAO.

	std::vector < GUITextVertex > vertices;
	float wh = Constants::getScreenHeight();
	float xPos = 0.0f;
	float yPos = wh - 0.0f;
	std::string s = mesh.getString();

	for (unsigned int i = 0; i < s.size(); i++) {

		stbtt_aligned_quad q;

		stbtt_GetBakedQuad(m_charData, m_bitmapWidth, m_bitmapHeight, s[i] - 32, & xPos, & yPos, & q, 1);

		renderQuad(vertices, glm::vec4(q.x0, wh - q.y0, q.x1, wh - q.y1), glm::vec4(q.s0, q.t0, q.s1, q.t1));

	}


	mesh.pushData(vertices);


	mesh.needsUpdate = false;
}

void GUIFont::renderQuad(std::vector < GUITextVertex > & vertices, const glm::vec4 & destRect, const glm::vec4 & uv) {
	vertices.emplace_back(glm::vec2(destRect.x, destRect.y), glm::vec2(uv.x, uv.y)); // Bottom Left
	vertices.emplace_back(glm::vec2(destRect.x, destRect.w), glm::vec2(uv.x, uv.w)); // Top Left
	vertices.emplace_back(glm::vec2(destRect.z, destRect.w), glm::vec2(uv.z, uv.w)); // Top Right
	vertices.emplace_back(glm::vec2(destRect.x, destRect.y), glm::vec2(uv.x, uv.y)); // Bottom Left
	vertices.emplace_back(glm::vec2(destRect.z, destRect.w), glm::vec2(uv.z, uv.w)); // Top Right
	vertices.emplace_back(glm::vec2(destRect.z, destRect.y), glm::vec2(uv.z, uv.y)); // Bottom Right
}