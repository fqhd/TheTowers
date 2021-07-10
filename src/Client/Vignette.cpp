#include "Vignette.hpp"

void Vignette::init(){
    m_quad.init();
    m_quadShader.init();
    m_framebuffer.init(1280, 720);
}

void Vignette::bindBuffer(){
    m_framebuffer.bind();
}

void Vignette::unbindBuffer(){
    m_framebuffer.unbind();
}

void Vignette::renderVignette(){
    m_quadShader.bind();
    glBindTexture(GL_TEXTURE_2D, m_framebuffer.getTextureID());
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    m_quad.render();
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_quadShader.unbind();
}

void Vignette::destroy(){
    m_framebuffer.destroy();
    m_quadShader.destroy();
    m_quad.destroy();
}
