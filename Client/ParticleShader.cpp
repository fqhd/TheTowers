#include "ParticleShader.hpp"

void ParticleShader::getUniformLocations(){
    bind();
    //Getting locations
    m_projectionLocation = glGetUniformLocation(m_programID, "projection");
    unbind();
}
void ParticleShader::loadProjection(const glm::mat4& matrix){
    glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, &matrix[0][0]);
}
