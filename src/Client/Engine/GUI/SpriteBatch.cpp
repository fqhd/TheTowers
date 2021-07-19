/*
The MIT License (MIT)

Copyright (c) 2015 Benjamin Arnold

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "SpriteBatch.hpp"
#include <algorithm>
#include <iostream>


Glyph::Glyph(const math::vec4& destRect, const math::vec4& uvRect, GLuint _texture, float _depth, const ColorRGBA8& color) {
	texture = _texture;
	depth = _depth;

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

void SpriteBatch::init() {
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

void SpriteBatch::begin() {
	m_renderBatches.clear();
	m_glyphs.clear();
}

void SpriteBatch::end() {
	m_glyphPointers.resize(m_glyphs.size());
	for (size_t i = 0; i < m_glyphs.size(); i++) {
		m_glyphPointers[i] = &m_glyphs[i];
	}
	std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareDepth);
	createRenderBatches();
}

void SpriteBatch::draw(const math::vec4& destRect, const math::vec4& uvRect, GLuint texture, const ColorRGBA8& color) {
	m_glyphs.emplace_back(destRect, uvRect, texture, m_currentDepth, color);
	m_currentDepth += 1.0f;
}

void SpriteBatch::render() {
	glBindVertexArray(m_vao);
	glDisable(GL_CULL_FACE);

	for (size_t i = 0; i < m_renderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
	}

	glEnable(GL_CULL_FACE);
	glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches() {
	std::vector<GUIVertex> vertices;

	vertices.resize(m_glyphPointers.size() * 6);

	if (m_glyphPointers.empty()) return;

	int offset = 0;
	int cv = 0;

	m_renderBatches.emplace_back(offset, 6, m_glyphPointers[0]->texture);
	vertices[cv++] = m_glyphPointers[0]->topLeft;
	vertices[cv++] = m_glyphPointers[0]->bottomLeft;
	vertices[cv++] = m_glyphPointers[0]->bottomRight;
	vertices[cv++] = m_glyphPointers[0]->bottomRight;
	vertices[cv++] = m_glyphPointers[0]->topRight;
	vertices[cv++] = m_glyphPointers[0]->topLeft;
	offset += 6;

	for (size_t cg = 1; cg < m_glyphPointers.size(); cg++) {
		if (m_glyphPointers[cg]->texture != m_glyphPointers[cg - 1]->texture) {
			m_renderBatches.emplace_back(offset, 6, m_glyphPointers[cg]->texture);
		} else {
			m_renderBatches.back().numVertices += 6;
		}
		vertices[cv++] = m_glyphPointers[cg]->topLeft;
		vertices[cv++] = m_glyphPointers[cg]->bottomLeft;
		vertices[cv++] = m_glyphPointers[cg]->bottomRight;
		vertices[cv++] = m_glyphPointers[cg]->bottomRight;
		vertices[cv++] = m_glyphPointers[cg]->topRight;
		vertices[cv++] = m_glyphPointers[cg]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GUIVertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(GUIVertex), vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool SpriteBatch::compareDepth(Glyph* a, Glyph* b) {
	return (a->depth < b->depth);
}