#include "Chunk.hpp"

Chunk::Chunk() {
	needsMeshUpdate = true;
	m_vaoID = 0;
	m_vboID = 0;
}

void Chunk::init(int _x, int _y, int _z) {
	x = _x;
	y = _y;
	z = _z;

	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);

	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	glEnableVertexAttribArray(0);

	glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Chunk::pushData() {
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_numVertices = vertices.size();
}

unsigned int Chunk::getNumVertices(){
	return m_numVertices;
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
