#pragma once

#include "Engine/Utils/Quad.hpp"
#include "Engine/Utils/QuadShader.hpp"
#include "Engine/Utils/Framebuffer.hpp"

class Vignette {
public:

    void init();
    void bindBuffer(); // Binds the framebuffer
    void unbindBuffer(); // Unbinds the framebuffer
    void renderVignette(); // Renders a quad with the vignette shader
    void destroy();

private:

    Quad m_quad;
    QuadShader m_quadShader;
    Framebuffer m_framebuffer;

};
