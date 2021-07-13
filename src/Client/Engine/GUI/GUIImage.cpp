#include "GUIImage.hpp"

void GUIImage::init(const glm::vec2& size, GLuint _textureID){
    m_textureID = _textureID;

    GUIImageVertex vertices = {
        GUIImageVertex(glm::vec2(0, 0), 0),
        GUIImageVertex(glm::vec2(0, size.y), 1),
        GUIImageVertex(glm::vec2(size.x, size.y), 2),

        GUIImageVertex(glm::vec2(0, 0), 0),
        GUIImageVertex(glm::vec2(size.x, size.y), 2),
        GUIImageVertex(glm::vec2(size.x, 0), 3)
    };

    glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GUIImageVertex), (void*)offsetof(GUIImageVertex, position));
	glVertexAttribPointer(1, 1, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(GUIImageVertex), (void*)offsetof(GUIImageVertex, textureInfo));

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GUIImage::render(){
    glBindVertexArray(m_vaoID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void GUIImage::destroy(){
    glDeleteVertexArrays(1, &m_vaoID);
	glDeleteBuffers(1, &m_vboID);
}

GLuint GUIImage::getTextureID(){
    return m_textureID;
}
