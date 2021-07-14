#include "GUIRenderer.hpp"
#include <cstddef>

void GUIRenderer::init() {
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (void*)offsetof(GUIVertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(GUIVertex), (void*)offsetof(GUIVertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (void*)offsetof(GUIVertex, textureInfo));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GUIRenderer::destroy() {
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	m_vertices.clear();
}

void GUIRenderer::begin() {
	m_vertices.clear();
}

void GUIRenderer::end() {
	uploadData();
}
 
void GUIRenderer::draw(const math::vec4& destRect, const ColorRGBA8& color, unsigned int layer) {
	m_vertices.emplace_back(glm::vec2(destRect.x, destRect.y), color, glm::vec2(0, layer));
	m_vertices.emplace_back(glm::vec2(destRect.x, destRect.y + destRect.w), color, glm::vec2(1, layer));
	m_vertices.emplace_back(glm::vec2(destRect.x + destRect.z, destRect.y + destRect.w), color, glm::vec2(2, layer));

	m_vertices.emplace_back(glm::vec2(destRect.x, destRect.y), color, glm::vec2(0, layer));
	m_vertices.emplace_back(glm::vec2(destRect.x + destRect.z, destRect.y + destRect.w), color, glm::vec2(2, layer));
	m_vertices.emplace_back(glm::vec2(destRect.x + destRect.z, destRect.y), color, glm::vec2(3, layer));
}

void GUIRenderer::render() {
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glBindVertexArray(m_vao);

	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());

	glBindVertexArray(0);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void GUIRenderer::uploadData() {
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices[0]) * m_vertices.size(), m_vertices.data(), GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
