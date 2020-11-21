#include "GUIFontShader.hpp"

void GUIFontShader::loadMatrix(const glm::mat4& matrix){
	glUniformMatrix4fv(m_matrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

void GUIFontShader::getUniformLocations(){
	bind();
	m_matrixLocation = glGetUniformLocation(m_programID, "matrix");
	m_colorLocation = glGetUniformLocation(m_programID, "textColor");
	unbind();
}

void GUIFontShader::loadColor(const ColorRGBA8& color){

	glm::vec3 c;
	c.x = color.r;
	c.y = color.g;
	c.z = color.b;

	glUniform4fv(m_colorLocation, 1, &c[0]);

}
