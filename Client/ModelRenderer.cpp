#include "ModelRenderer.hpp"

void ModelRenderer::init(){

    m_shader.loadShader("res/shaders/modelVertex.glsl", "res/shaders/modelFragment.glsl");
    m_shader.getUniformLocations();

}

void ModelRenderer::render(Camera& camera){

    m_shader.bind();
    m_shader.loadProjection(camera.getProjectionMatrix());
    m_shader.loadView(camera.getViewMatrix());

    for(auto& i : entities){
        m_shader.loadModel(i.transform.getMatrix());
        m_shader.loadColor(i.getColor());
        i.render();
    }

    m_shader.unbind();

}

void ModelRenderer::destroy(){
    m_shader.destroy();
}
