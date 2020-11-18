#pragma once
#include "Vertex.hpp"
#include "GUIRenderer.hpp"
#include <glm/glm.hpp>

class Image {
public:


     Image(const glm::vec4& destRect, const ColorRGBA8& color);
     void render(GUIRenderer& renderer);



private:

     glm::vec4 m_destRect;
     ColorRGBA8 m_color;

};
