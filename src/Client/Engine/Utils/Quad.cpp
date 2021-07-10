#include "Quad.hpp"

void Quad::init(){
    QuadVertex vertices[] = {
        QuadVertex(glm::vec2(-1, -1), glm::vec2(0, 0)),
        QuadVertex(glm::vec2(-1, 1), glm::vec2(0, 1)),
        QuadVertex(glm::vec2(1, 1), glm::vec2(1, 1)),
        QuadVertex(glm::vec2(-1, -1), glm::vec2(0, 0)),
        QuadVertex(glm::vec2(1, 1), glm::vec2(1, 1)),
        QuadVertex(glm::vec2(1, -1), glm::vec2(1, 0)),
    };

    glGenVertexArrays(1, &m_vaoID);
    glBindVertexArray(m_vaoID);

    glGenBuffers(1, &m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, position));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, uv));
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
