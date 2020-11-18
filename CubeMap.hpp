#pragma once
#include "CubeMapRenderer.hpp"
#include "CubeMapTexture.hpp"
#include "CubeMapShader.hpp"

class CubeMap {
public:
     
    void init();
    void update();
    void render(const glm::mat4& projection, const glm::mat4& view);
    void destroy();

private:


    CubeMapTexture m_dayTexture;
    CubeMapRenderer m_cube;
    CubeMapShader m_shader;


};
