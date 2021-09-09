#include "SpriteBatch.hpp"
#include <algorithm>
#include <iostream>


Glyph::Glyph(const math::vec4& destRect, const math::vec4& uvRect, const ColorRGBA8& color) {
	topLeft.color = color;
	topLeft.setPosition(destRect.x, destRect.y + destRect.w);
	topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	bottomLeft.color = color;
	bottomLeft.setPosition(destRect.x, destRect.y);
	bottomLeft.setUV(uvRect.x, uvRect.y);

	bottomRight.color = color;
	bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	topRight.color = color;
	topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
}

void SpriteBatch::init(GLuint textureID) {
	m_textureID = textureID;
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (void*)offsetof(GUIVertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (void*)offsetof(GUIVertex, uv));
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(GUIVertex), (void*)offsetof(GUIVertex, color));

	glBindVertexArray(0);
}

void SpriteBatch::destroy() {
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}

void SpriteBatch::draw(const math::vec4& destRect, const math::vec4& uvRect, const ColorRGBA8& color) {
	m_glyphs.emplace_back(destRect, uvRect, color);
}

void SpriteBatch::batch() {
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_glyphs.size() * sizeof(Glyph), m_glyphs.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::render() {
	glDisable(GL_CULL_FACE);
	glBindVertexArray(m_vao);

	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glDrawArrays(GL_TRIANGLES, 0, m_glyphs.size() * 6);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
	glEnable(GL_CULL_FACE);
}
