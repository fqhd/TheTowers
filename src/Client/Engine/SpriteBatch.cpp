#include "SpriteBatch.hpp"
#include <algorithm>
#include <iostream>


void SpriteBatch::init(GLuint textureID) {
	m_textureID = textureID;
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (void*)8);
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(GUIVertex), (void*)16);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, const ColorRGBA8& color) {
	m_vertices.emplace_back(destRect.x, destRect.y, uvRect.x, uvRect.y, color);
	m_vertices.emplace_back(destRect.x, destRect.y + destRect.w, uvRect.x, uvRect.y + uvRect.w, color);
	m_vertices.emplace_back(destRect.x + destRect.z, destRect.y + destRect.w, uvRect.x + uvRect.z, uvRect.y + uvRect.w, color);

	m_vertices.emplace_back(destRect.x, destRect.y, uvRect.x, uvRect.y, color);
	m_vertices.emplace_back(destRect.x + destRect.z, destRect.y + destRect.w, uvRect.x + uvRect.z, uvRect.y + uvRect.w, color);
	m_vertices.emplace_back(destRect.x + destRect.z, destRect.y, uvRect.x + uvRect.z, uvRect.y, color);
}

void SpriteBatch::batch() {
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GUIVertex), m_vertices.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_vertexCount = m_vertices.size();
	m_vertices.resize(0);
}

void SpriteBatch::render() {
	glDisable(GL_CULL_FACE);
	glBindVertexArray(m_vao);

	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
	glEnable(GL_CULL_FACE);
}

void SpriteBatch::destroy() {
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}