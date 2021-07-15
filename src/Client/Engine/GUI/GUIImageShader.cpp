#include "GUIImageShader.hpp"

void GUIImageShader::init(){
    loadShader("res/shaders/gui_image_vertex_shader.glsl", "res/shaders/gui_image_fragment_shader.glsl");
    getUniformLocations();
}

void GUIImageShader::loadMatrix(const math::mat4& matrix){
    glUniformMatrix4fv(m_matrixLocation, 1, GL_FALSE, &matrix.m[0][0]);
}

void GUIImageShader::loadPosition(const math::vec2& position){
    glUniform2fv(m_positionLocation, 1, &position.x);
}

void GUIImageShader::getUniformLocations(){
    bind();
    m_positionLocation = glGetUniformLocation(m_programID, "positionOffset");
    m_matrixLocation = glGetUniformLocation(m_programID, "matrix");
    unbind();
}
