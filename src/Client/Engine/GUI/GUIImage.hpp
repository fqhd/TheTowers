#pragma once

#include "../Utils/Vertex.hpp"
#include "../Math/Math.hpp"

class GUIImage {
public:

    GUIImage(const math::vec4& destRect, GLuint _textureID);
    void render();
    void destroy();
    GLuint getTextureID();
    const math::vec2& getPosition();


private:

    GLuint m_vaoID = 0;
    GLuint m_vboID = 0;
    GLuint m_textureID = 0;
    math::vec2 m_position;

};
