#include "GUIShader.hpp"

void GUIShader::loadMatrix(const glm::mat4& matrix){
	glUniformMatrix4fv(m_matrix, 1, GL_FALSE, &matrix[0][0]);
}

void GUIShader::getUniformLocations(){
	bind();
	m_matrix = glGetUniformLocation(m_programID, "matrix");
	unbind();
}
