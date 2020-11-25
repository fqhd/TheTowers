#include "ModelShader.hpp"




void ModelShader::getUniformLocations(){
	bind();

	m_projection = glGetUniformLocation(m_programID, "projection");
	m_view = glGetUniformLocation(m_programID, "view");
	m_model = glGetUniformLocation(m_programID, "model");
	m_colorLocation = glGetUniformLocation(m_programID, "color");


	unbind();
}

void ModelShader::loadColor(const ColorRGBA8& color){
	glm::vec3 c;

	c.x = color.r / 255.0f;
	c.y = color.g / 255.0f;
	c.z = color.b / 255.0f;

	glUniform3fv(m_colorLocation, 1, &c[0]);
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
