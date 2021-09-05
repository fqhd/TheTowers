#include "ParticleQuad.hpp"

void ParticleQuad::init(){
	// Sending position data to vbo
	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);
	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 16, 0);
	glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, 16, (void*)12);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ParticleQuad::pushData(const void* _data, unsigned int _size){
	if(!_data)return;
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, _size * sizeof(ParticleInstance), _data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ParticleQuad::render(unsigned int _numInstances){
	glBindVertexArray(m_vaoID);
	glPointSize(10.0f);
	glDrawArrays(GL_POINTS, 0, _numInstances);
	glBindVertexArray(0);
}

void ParticleQuad::destroy(){
	glDeleteVertexArrays(1, &m_vaoID);
	glDeleteBuffers(1, &m_vboID);
}
