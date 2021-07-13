#include "GUIImageRenderer.hpp"

void GUIImageRenderer::init(){
    m_shader.init();
}

void GUIImageRenderer::render(){
    m_shader.bind();

    for(auto& i : images){
        m_shader.loadPosition(i.position);
        i.render();
    }

    m_shader.unbind();
}

void GUIImageRenderer::destroy(){
    for(auto& i : images){
        i.destroy();
    }
    m_shader.destroy();
}
