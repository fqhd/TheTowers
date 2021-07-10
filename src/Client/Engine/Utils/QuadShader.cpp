#include "QuadShader.hpp"

void QuadShader::init(){
    loadShader("res/shaders/vignette_vertex_shader.glsl", "res/shaders/vignette_fragment_shader.glsl");
    getUniformLocations();
}

void QuadShader::setToggle(bool _toggle){
    glUniform1i(m_toggleLocation, _toggle);
}

void QuadShader::getUniformLocations(){
    bind();
    m_toggleLocation = glGetUniformLocation(m_programID, "toggled");
    unbind();
}
