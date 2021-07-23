#include "EntityShader.hpp"


void EntityShader::init(){
	loadShader("res/shaders/entity_vertex_shader.glsl", "res/shaders/entity_fragment_shader.glsl");
	getUniformLocations();
}

void EntityShader::loadTeam(bool team){
	glUniform1i(m_teamLocation, m_programID);
}

void EntityShader::getUniformLocations(){
	bind();
	m_teamLocation = glGetUniformLocation(m_programID, "team");
	m_viewLocation = glGetUniformLocation(m_programID, "view");
	m_projectionLocation = glGetUniformLocation(m_programID, "projection");
	m_modelLocation = glGetUniformLocation(m_programID, "model");
	unbind();
}

void EntityShader::loadProjectionMatrix(const math::mat4& matrix){
	glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, &matrix.m[0][0]);
}

void EntityShader::loadModelMatrix(const math::mat4& matrix){
	glUniformMatrix4fv(m_modelLocation, 1, GL_FALSE, &matrix.m[0][0]);
}

void EntityShader::loadViewMatrix(const math::mat4& matrix){
	glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, &matrix.m[0][0]);
}
