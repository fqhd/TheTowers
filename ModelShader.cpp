#include "ModelShader.hpp"




void ModelShader::getUniformLocations(){
	bind();

	m_projection = glGetUniformLocation(m_programID, "projection");
	m_view = glGetUniformLocation(m_programID, "view");
	m_model = glGetUniformLocation(m_programID, "model");
	

	unbind();
}


void ModelShader::loadProjection(const glm::mat4& matrix){
	glUniformMatrix4fv(m_projection, 1, GL_FALSE, &matrix[0][0]);
}

void ModelShader::loadView(const glm::mat4& matrix){
	glUniformMatrix4fv(m_view, 1, GL_FALSE, &matrix[0][0]);
}

void ModelShader::loadModel(const glm::mat4& matrix){
	glUniformMatrix4fv(m_model, 1, GL_FALSE, &matrix[0][0]);
}