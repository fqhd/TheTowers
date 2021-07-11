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
	m_lightDirectionLocation = glGetUniformLocation(m_programID, "lightDir");
	m_teamLocation = glGetUniformLocation(m_programID, "isBlueTeam");
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

void ModelShader::loadTeam(bool isBlueTeam){
	glUniform1i(m_teamLocation, isBlueTeam);
}

void ModelShader::loadGradient(float gradient){
	glUniform1f(m_gradientLocation, gradient);
}

void ModelShader::loadDensity(float density){
	glUniform1f(m_densityLocation, density);
}
