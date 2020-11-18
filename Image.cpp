#include "Image.hpp"

Image::Image(const glm::vec4& destRect, const ColorRGBA8& color){
     m_destRect = destRect;
     m_color = color;
}

void Image::render(GUIRenderer& renderer){
     renderer.draw(m_destRect, m_color);
}
