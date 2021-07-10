#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>
#include <iostream>

class Framebuffer {
public:

    void init(unsigned int _w, unsigned int _h);
    void bind();
    void unbind();
    void destroy();

    GLuint getTextureID();

private:

    GLuint m_fboID = 0;
    GLuint m_rboID = 0;
    GLuint m_textureID = 0;

};

#endif
