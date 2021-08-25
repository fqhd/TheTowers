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

#pragma once

#include <epoxy/gl.h>
#include <vector>

#include "Math.hpp"
#include "Vertex.hpp"

class Glyph {
public:
	Glyph() {};
	Glyph(const math::vec4& destRect, const math::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& color);

	GLuint texture;
	float depth;
	GUIVertex topLeft;
	GUIVertex bottomLeft;
	GUIVertex topRight;
	GUIVertex bottomRight;
};

class RenderBatch {
public:
	RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset),
		numVertices(NumVertices), texture(Texture) {
	}
	GLuint offset;
	GLuint numVertices;
	GLuint texture;
};

class SpriteBatch {
public:

	void init();
	void begin();
	void draw(const math::vec4& destRect, const math::vec4& uvRect, GLuint texture, const ColorRGBA8& color);
	void end();
	void render();
	void destroy();

private:
	void createRenderBatches();

	static bool compareDepth(Glyph* a, Glyph* b);

	// m_currentDepth because I want the depth to be based on order instead of specifying the depth of the glyphs in the arguments
	float m_currentDepth = 1.0f;
	GLuint m_vbo;
	GLuint m_vao;

	std::vector<Glyph*> m_glyphPointers;
	std::vector<Glyph> m_glyphs;
	std::vector<RenderBatch> m_renderBatches;
};
