#pragma once

#include "../Utils/Vertex.hpp"

class GUIImage {
public:

    void init(const glm::vec4& destRect, GLuint _textureID);
    void render();
    void destroy();
    GLuint getTextureID();

    glm::vec2 position;

private:

    GLuint m_vaoID = 0;
    GLuint m_vboID = 0;
    GLuint m_textureID = 0;

};
