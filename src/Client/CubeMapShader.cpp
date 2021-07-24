#include "CubeMapShader.hpp"


void CubeMapShader::init(){
	loadShader("res/shaders/cubemap_vertex_shader.glsl", "res/shaders/cubemap_fragment_shader.glsl");
	bind();
	getUniformLocations();
	unbind();
}

void CubeMapShader::loadProjection(const math::mat4& matrix) {
	glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, &matrix.m[0][0]);
}

void CubeMapShader::loadView(const math::mat4& matrix){
	glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, &matrix.m[0][0]);
}

void CubeMapShader::getUniformLocations(){
	m_viewLocation = glGetUniformLocation(m_programID, "view");
	m_projectionLocation = glGetUniformLocation(m_programID, "projection");
}
