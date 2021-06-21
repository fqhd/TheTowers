#include "Chunk.hpp"

Chunk::Chunk() {
	needsUpdate = true;
	m_vaoID = 0;
	m_vboID = 0;
}

void Chunk::init(int _x, int _y, int _z, uint8_t* _dataptr) {

	x = _x;
	y = _y;
	z = _z;
	m_data = _dataptr;

	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);

	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Chunk::pushData(GLuint* vertices, unsigned int numVertices) {

	m_numVertices = numVertices;

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * numVertices, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

unsigned int Chunk::getNumVertices(){
	return m_numVertices;
}

void Chunk::updateData(){
	for(unsigned int y = 0; y < CHUNK_WIDTH; y++){
		for(unsigned int z = 0; z < CHUNK_WIDTH; z++){
			for(unsigned int x = 0; x < CHUNK_WIDTH; x++){
				if(y == 0){
					setBlock(x, y, z, 2);
				}
			}	
		}	
	}
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

uint8_t Chunk::getBlock(uint8_t _x, uint8_t _y, uint8_t _z){
	if(_x < 0 || _x >= CHUNK_WIDTH) return 0;
	if(_y < 0 || _y >= CHUNK_WIDTH) return 0;
	if(_z < 0 || _z >= CHUNK_WIDTH) return 0;

	return m_data[(_y * CHUNK_WIDTH * CHUNK_WIDTH) + (_z * CHUNK_WIDTH) + _x];
}

void Chunk::setBlock(uint8_t _x, uint8_t _y, uint8_t _z, uint8_t _blockID){
	if(_x < 0 || _x >= CHUNK_WIDTH) return;
	if(_y < 0 || _y >= CHUNK_WIDTH) return;
	if(_z < 0 || _z >= CHUNK_WIDTH) return;

	m_data[(_y * CHUNK_WIDTH * CHUNK_WIDTH) + (_z * CHUNK_WIDTH) + _x] = _blockID;
}