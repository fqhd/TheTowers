#pragma once
#include <GL/glew.h>

class CubeMapRenderer {
public:

    void init();
    void render();
    void destroy();

private:

    GLuint m_vaoID;
    GLuint m_vboID;

};