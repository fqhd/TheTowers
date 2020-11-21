#include "CubeMapShader.hpp"
#include "Shader.hpp"

void CubeMapShader::loadProjection(const glm::mat4& matrix) {
    glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, &matrix[0][0]);
}

void CubeMapShader::loadView(const glm::mat4& matrix){
    glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, &matrix[0][0]);
}

void CubeMapShader::getUniformLocations(){
    bind();
    m_viewLocation = glGetUniformLocation(m_programID, "view");
    m_projectionLocation = glGetUniformLocation(m_programID, "projection");
    unbind();
}