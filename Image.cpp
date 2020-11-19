#include "Image.hpp"

Image::Image(const glm::vec4& d, const ColorRGBA8& c){
     destRect = d;
     color = c;
}

void Image::render(GUIRenderer& renderer){
     renderer.draw(destRect, color);
}
