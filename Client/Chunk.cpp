#include "Chunk.hpp"
#include "Constants.hpp"


void Chunk::init(int x, int y, int z){

	m_x = x;
	m_y = y;
	m_z = z;

	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);

	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

unsigned int Chunk::getNumVertices(){
	return m_numVertices;
}


void Chunk::pushData(const std::vector<Vertex>& vertices){

	m_numVertices = vertices.size();

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}


void Chunk::render(){
	glBindVertexArray(m_vaoID);
	glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
	glBindVertexArray(0);
}

int Chunk::getX(){
	return m_x;
}

int Chunk::getY(){
	return m_y;
}

int Chunk::getZ(){
	return m_z;
}


void Chunk::setX(int x){
	m_x = x;
}

void Chunk::setY(int y) {
	m_y = y;
}

void Chunk::setZ(int z){
	m_z = z;
}


void Chunk::destroy(){
	glDeleteVertexArrays(1, &m_vaoID);
	glDeleteBuffers(1, &m_vboID);
}
