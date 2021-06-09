#include "Chunk.hpp"
#include "../../Constants.hpp"

Chunk::Chunk() {
	needsUpdate = true;
	m_vaoID = 0;
	m_vboID = 0;
}

void Chunk::init(int _x, int _y, int _z) {

	x = _x;
	y = _y;
	z = _z;

	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);

	glGenBuffers(1, & m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Chunk::pushData(Vertex* vertices, unsigned int numVertices) {

	m_numVertices = numVertices;

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numVertices, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	size = sizeof(vertices[0]) * numVertices;

}


void Chunk::render() {
	glBindVertexArray(m_vaoID);
	glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
	glBindVertexArray(0);
}

void Chunk::destroy() {
	glDeleteVertexArrays(1, & m_vaoID);
	glDeleteBuffers(1, & m_vboID);
}