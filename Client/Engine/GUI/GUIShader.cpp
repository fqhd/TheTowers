#include "GUIShader.hpp"

void GUIShader::init(){
	loadShader("res/shaders/gui_vertex_shader.glsl", "res/shaders/gui_fragment_shader.glsl");
	bind();
	getUniformLocations();
	unbind();
}

void GUIShader::loadMatrix(const glm::mat4& matrix){
	glUniformMatrix4fv(m_matrix, 1, GL_FALSE, &matrix[0][0]);
}

void GUIShader::getUniformLocations(){
	m_matrix = glGetUniformLocation(m_programID, "matrix");
}
