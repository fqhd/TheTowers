#pragma once

#include "Vertex.hpp"
#include <GL/glew.h>

class VignetteQuad {
public:

    void init();
    void render();
    void destroy();

private:

    GLuint m_vaoID = 0;
    GLuint m_vboID = 0;

};
