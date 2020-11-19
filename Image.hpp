#pragma once
#include "Vertex.hpp"
#include "GUIRenderer.hpp"
#include <glm/glm.hpp>

class Image {
public:


     Image(const glm::vec4& d, const ColorRGBA8& c);
     void render(GUIRenderer& renderer);

     glm::vec4 destRect;
     ColorRGBA8 color;

private:


};
