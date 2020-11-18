#include "CubeMap.hpp"

void CubeMap::init(){

    std::vector<std::string> locations;

    locations.push_back("res/textures/cubemap/right.jpg");
    locations.push_back("res/textures/cubemap/left.jpg");
    locations.push_back("res/textures/cubemap/top.jpg");
    locations.push_back("res/textures/cubemap/bottom.jpg");
    locations.push_back("res/textures/cubemap/front.jpg");
    locations.push_back("res/textures/cubemap/back.jpg");

    m_dayTexture.init(locations);
    m_cube.init();
    m_shader.loadShader("res/shaders/cubemapVertex.glsl", "res/shaders/cubemapFragment.glsl");
    m_shader.getUniformLocations();

}

void CubeMap::update(){

}

void CubeMap::render(const glm::mat4& projection, const glm::mat4& view){
    glDepthFunc(GL_LEQUAL);
    m_shader.bind();
    m_dayTexture.bind();

    m_shader.loadProjection(projection);
    m_shader.loadView(view);

    m_cube.render();

    m_dayTexture.unbind();
    m_shader.unbind();
    glDepthFunc(GL_LESS);
}


void CubeMap::destroy(){

    m_cube.destroy();
    m_shader.destroy();
    m_dayTexture.destroy();

}