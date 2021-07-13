#include "GUIFontShader.hpp"
void GUIFontShader::init(){
	loadShader("res/shaders/font_vertex_shader.glsl", "res/shaders/font_fragment_shader.glsl");
	getUniformLocations();
}

void GUIFontShader::loadMatrix(const glm::mat4& matrix){
	glUniformMatrix4fv(m_matrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void GUIFontShader::getUniformLocations(){
	bind();
	m_matrixLocation = glGetUniformLocation(m_programID, "matrix");
	m_colorLocation = glGetUniformLocation(m_programID, "color");
	m_positionLocation = glGetUniformLocation(m_programID, "position");
	unbind();
}

void GUIFontShader::loadPosition(const glm::vec2& position){
	glUniform2fv(m_positionLocation, 1, &position[0]);
}

void GUIFontShader::loadColor(const ColorRGBA8& color){
	math::vec4 c;

	c.x = color.r/255.0f;
	c.y = color.g/255.0f;
	c.z = color.b/255.0f;
	c.w = color.a/255.0f;

	glUniform4fv(m_colorLocation, 1, &c.x);
}
