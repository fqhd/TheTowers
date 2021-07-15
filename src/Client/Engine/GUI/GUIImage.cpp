#include "GUIImage.hpp"
#include <iostream>

GUIImage::GUIImage(const math::vec4& destRect, GLuint _textureID){
	m_textureID = _textureID;
	m_position.x = destRect.x;
	m_position.y = destRect.y;

	GUITextVertex vertices[] = { // We can use a text vertex because it's okay in this case, we only care about the position and the UV
		GUITextVertex(glm::vec2(0, 0), glm::vec2(0, 0)),
		GUITextVertex(glm::vec2(0, destRect.w), glm::vec2(0, 1)),
		GUITextVertex(glm::vec2(destRect.z, destRect.w), glm::vec2(1, 1)),

		GUITextVertex(glm::vec2(0, 0), glm::vec2(0, 0)),
		GUITextVertex(glm::vec2(destRect.z, destRect.w), glm::vec2(1, 1)),
		GUITextVertex(glm::vec2(destRect.z, 0), glm::vec2(1, 0))
	};

	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);

	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GUITextVertex), (void*)offsetof(GUITextVertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GUITextVertex), (void*)offsetof(GUITextVertex, uv));

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GUIImage::render(){
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glBindVertexArray(m_vaoID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void GUIImage::destroy(){
	glDeleteVertexArrays(1, &m_vaoID);
	glDeleteBuffers(1, &m_vboID);
}

GLuint GUIImage::getTextureID(){
	return m_textureID;
}

const math::vec2& GUIImage::getPosition(){
	return m_position;
}