#pragma once

#include "Engine/Utils/Quad.hpp"
#include "Engine/Utils/QuadShader.hpp"

class Vignette {
public:

    void init();
    void renderVignette(); // Renders a quad with the vignette shader
    void destroy();

private:

    Quad m_quad;
    QuadShader m_quadShader;

};
