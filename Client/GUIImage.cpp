#include "GUIImage.hpp"

GUIImage::GUIImage(const glm::vec4& d, const ColorRGBA8& c){
     destRect = d;
     color = c;
}

void GUIImage::render(GUIRenderer& renderer){
     renderer.draw(destRect, color);
}
