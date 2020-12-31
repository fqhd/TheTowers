#include "CubeMap.hpp"

void CubeMap::init(){

    std::vector<std::string> locations;

    locations.push_back("res/textures/cubemap/right.png");
    locations.push_back("res/textures/cubemap/left.png");
    locations.push_back("res/textures/cubemap/top.png");
    locations.push_back("res/textures/cubemap/bottom.png");
    locations.push_back("res/textures/cubemap/back.png");
    locations.push_back("res/textures/cubemap/front.png");

    m_dayTexture.init(locations);
    m_cube.init();
    m_shader.init();

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
