#include "ParticleQuad.hpp"

void ParticleQuad::init(){
	
	float vertices[] = {
	  0.0f, 0.0f,
	  0.0f, 1.0f,
	  1.0f, 1.0f,
	  0.0f, 0.0f,
	  1.0f, 1.0f,
	  1.0f, 0.0f
	};

	// Sending position data to vbo
	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);
	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Generating the matrices buffer
	glGenBuffers(1, &m_mvboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_mvboID);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(math::mat4), 0);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(math::mat4), (void*)(1 * sizeof(math::vec4)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(math::mat4), (void*)(2 * sizeof(math::vec4)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(math::mat4), (void*)(3 * sizeof(math::vec4)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Generating the texture indices buffer
	glGenBuffers(1, &m_uvboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvboID);
	glEnableVertexAttribArray(5);
	glVertexAttribIPointer(5, 1, GL_UNSIGNED_INT, sizeof(unsigned int), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	glBindVertexArray(0);
}

void ParticleQuad::pushMatrices(const void* _data, unsigned int _size){
	glBindBuffer(GL_ARRAY_BUFFER, m_mvboID);
	glBufferData(GL_ARRAY_BUFFER, _size * sizeof(math::mat4), _data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ParticleQuad::pushTextureIndices(const void* _data, unsigned int _size){
	if(!_data)return;
	glBindBuffer(GL_ARRAY_BUFFER, m_uvboID);
	glBufferData(GL_ARRAY_BUFFER, _size * sizeof(unsigned int), _data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ParticleQuad::render(unsigned int _numInstances){
	glBindVertexArray(m_vaoID);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, _numInstances);
	glBindVertexArray(0);
}

void ParticleQuad::destroy(){
	glDeleteVertexArrays(1, &m_vaoID);
	glDeleteBuffers(1, &m_vboID);
	glDeleteBuffers(1, &m_mvboID);
	glDeleteBuffers(1, &m_uvboID);
}
