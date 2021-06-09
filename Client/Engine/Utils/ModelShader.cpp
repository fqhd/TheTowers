#include "ModelShader.hpp"


void ModelShader::init(){
	loadShader("res/shaders/model_vertex_shader.glsl", "res/shaders/model_fragment_shader.glsl");
	bind();
	getUniformLocations();
	unbind();
}

void ModelShader::getUniformLocations(){
	m_viewMatrixLocation = glGetUniformLocation(m_programID, "view");
	m_projectionMatrixLocation = glGetUniformLocation(m_programID, "projection");
	m_modelMatrixLocation = glGetUniformLocation(m_programID, "model");
	m_gradientLocation = glGetUniformLocation(m_programID, "gradient");
	m_densityLocation = glGetUniformLocation(m_programID, "density");
	m_colorLocation = glGetUniformLocation(m_programID, "color");
	m_lightDirectionLocation = glGetUniformLocation(m_programID, "lightDir");
}

void ModelShader::loadLightDirection(const glm::vec3& lightDir){
	glUniform3fv(m_lightDirectionLocation, 1, &lightDir[0]);
}

void ModelShader::loadViewMatrix(const glm::mat4& matrix){
	glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void ModelShader::loadProjectionMatrix(const glm::mat4& matrix){
	glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void ModelShader::loadModelMatrix(const glm::mat4& matrix){
	glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void ModelShader::loadGradient(float gradient){
	glUniform1f(m_gradientLocation, gradient);
}

void ModelShader::loadDensity(float density){
	glUniform1f(m_densityLocation, density);
}

void ModelShader::loadColor(const vec3& color){
	glm::vec3 floatColor = glm::vec3(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
	glUniform3fv(m_colorLocation, 1, &floatColor[0]);
}
