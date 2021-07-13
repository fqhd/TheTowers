#pragma once

#include "../Utils/Vertex.hpp"

class GUIImage {
public:

    void init(const glm::vec4& destRect);
    void render();
    void destroy();
    GLuint getTextureID();

private:

    GLuint m_vaoID = 0;
    GLuint m_vboID = 0;
    GLuint m_textureID = 0;

};
