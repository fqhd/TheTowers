#include "ChunkShader.hpp"
#include <iostream>

void ChunkShader::init(){
	loadShader("res/shaders/chunk_vertex_shader.glsl", "res/shaders/chunk_fragment_shader.glsl");
	bind();
	getUniformLocations();
	unbind();
}

void ChunkShader::getUniformLocations(){
	m_viewMatrixLocation = glGetUniformLocation(m_programID, "view");
	m_projectionMatrixLocation = glGetUniformLocation(m_programID, "projection");
	m_gradientLocation = glGetUniformLocation(m_programID, "gradient");
	m_densityLocation = glGetUniformLocation(m_programID, "density");
}

void ChunkShader::loadViewMatrix(const glm::mat4& matrix){
	glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void ChunkShader::loadProjectionMatrix(const glm::mat4& matrix){
	glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void ChunkShader::loadGradient(float gradient){
	glUniform1f(m_gradientLocation, gradient);
}

void ChunkShader::loadDensity(float density){
	glUniform1f(m_densityLocation, density);
}
