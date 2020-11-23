#pragma once
#include "GUIComponent.hpp"

class GUISelectbox {
public:

     GUISelectbox(const glm::vec4& quad, const ColorRGBA8& color, unsigned int numComponents);
     void update(InputManager& manager);
     void render(GUIRenderer& renderer);

     std::vector<GUIComponent> components;


private:


};
