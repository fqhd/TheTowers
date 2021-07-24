#include "ParticleShader.hpp"

void ParticleShader::init(){
	loadShader("res/shaders/particle_vertex_shader.glsl", "res/shaders/particle_fragment_shader.glsl");
	bind();
	getUniformLocations();
	unbind();
}

void ParticleShader::getUniformLocations(){
	m_projectionLocation = glGetUniformLocation(m_programID, "projection");
}
void ParticleShader::loadProjection(const math::mat4& matrix){
	glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, &matrix.m[0][0]);
}
