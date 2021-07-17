#include "GUIShader.hpp"

void SpriteShader::init(){
	loadShader("res/shaders/sprite_vertex_shader.glsl", "res/shaders/sprite_fragment_shader.glsl");
	getUniformLocations();
}

void SpriteShader::loadMatrix(const math::mat4& matrix){
	glUniformMatrix4fv(m_matrixLocation, 1, GL_FALSE, &matrix.m[0][0]);
}

void SpriteShader::getUniformLocations(){
	bind();
	m_matrixLocation = glGetUniformLocation(m_programID, "matrix");
	unbind();
}
