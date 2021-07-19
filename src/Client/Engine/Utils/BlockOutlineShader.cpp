#include "BlockOutlineShader.hpp"


void BlockOutlineShader::init() {
	loadShader("res/shaders/block_outline_vertex_shader.glsl", "res/shaders/block_outline_fragment_shader.glsl");
	getUniformLocations();
}

void BlockOutlineShader::getUniformLocations() {
	bind();
	m_viewMatrixLocation = glGetUniformLocation(m_programID, "view");
	m_projectionMatrixLocation = glGetUniformLocation(m_programID, "projection");
	m_blockPositionLocation = glGetUniformLocation(m_programID, "blockPosition");
	unbind();
}

void BlockOutlineShader::loadViewMatrix(const math::mat4& matrix) {
	glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE, &matrix.m[0][0]);
}

void BlockOutlineShader::loadProjectionMatrix(const math::mat4& matrix) {
	glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, &matrix.m[0][0]);
}

void BlockOutlineShader::loadBlockPosition(const math::ivec3& position) {
	math::vec3 p;
	p.x = position.x;
	p.y = position.y;
	p.z = position.z;
	glUniform3fv(m_blockPositionLocation, 1, &p.x);
}