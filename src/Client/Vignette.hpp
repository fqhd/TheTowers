#pragma once

#include "Engine/Utils/Quad.hpp"
#include "Engine/Utils/QuadShader.hpp"

class Vignette {
public:

    void init();
    void render(); // Renders a quad with the vignette shader
    void destroy();
    void setToggle(bool _toggle);

private:

    Quad m_quad;
    QuadShader m_quadShader;


};
