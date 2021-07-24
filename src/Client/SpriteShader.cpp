#include "SpriteShader.hpp"

void SpriteShader::init(){
	loadShader("res/shaders/sprite_vertex_shader.glsl", "res/shaders/sprite_fragment_shader.glsl");
	getUniformLocations();
}

void SpriteShader::loadMatrix(const math::mat4& _matrix){
	glUniformMatrix4fv(m_matrixLocation, 1, GL_FALSE, &_matrix.m[0][0]);
}

void SpriteShader::loadIsFont(bool _isFont){
	glUniform1i(m_isFontLocation, _isFont);
}

void SpriteShader::getUniformLocations(){
	bind();
	m_matrixLocation = glGetUniformLocation(m_programID, "matrix");
	m_isFontLocation = glGetUniformLocation(m_programID, "isFont");
	unbind();
}
