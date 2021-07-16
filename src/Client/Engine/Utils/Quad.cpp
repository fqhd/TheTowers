#include "Quad.hpp"

void Quad::init(){
    math::vec2 vertices[] = {
        math::vec2(-1, -1),
        math::vec2(-1, 1),
        math::vec2(1, 1),
        math::vec2(-1, -1),
        math::vec2(1, 1),
        math::vec2(1, -1)
    };

    glGenVertexArrays(1, &m_vaoID);
    glBindVertexArray(m_vaoID);

    glGenBuffers(1, &m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(math::vec2), 0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Quad::render(){
    glBindVertexArray(m_vaoID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Quad::destroy(){
    glDeleteVertexArrays(1, &m_vaoID);
	glDeleteBuffers(1, &m_vboID);
}
