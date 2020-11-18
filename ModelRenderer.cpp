#include "ModelRenderer.hpp"

void ModelRenderer::init(){

    m_shader.loadShader("res/shaders/modelVertex.glsl", "res/shaders/modelFragment.glsl");
    m_shader.getUniformLocations();

}

void ModelRenderer::render(Camera& camera){

    m_shader.bind();
    m_shader.loadProjection(camera.getProjectionMatrix());
    m_shader.loadView(camera.getViewMatrix());

    for(auto& i : models){
        m_shader.loadModel(i.transform.getMatrix());
        i.render();
    }

    m_shader.unbind();

}

void ModelRenderer::destroy(){
    for(auto& i : models){
        m_shader.loadModel(i.transform.getMatrix());
        i.destroy();
    }
    m_shader.destroy();
}