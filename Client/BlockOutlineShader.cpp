#include "BlockOutlineShader.hpp"


void BlockOutlineShader::init(){
     loadShader("res/shaders/block_outline_vertex_shader.glsl", "res/shaders/block_outline_fragment_shader.glsl");
     bind();
     getUniformLocations();
     unbind();
}

void BlockOutlineShader::getUniformLocations(){
     m_viewMatrixLocation = glGetUniformLocation(m_programID, "view");
     m_projectionMatrixLocation = glGetUniformLocation(m_programID, "projection");
     m_modelMatrixLocation = glGetUniformLocation(m_programID, "model");
}

void BlockOutlineShader::loadViewMatrix(const glm::mat4& matrix){
	glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void BlockOutlineShader::loadProjectionMatrix(const glm::mat4& matrix){
	glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void BlockOutlineShader::loadModelMatrix(const glm::mat4& matrix){
	glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}
