#pragma once
#include "Vertex.hpp"
#include "InputManager.hpp"
#include "GUIRenderer.hpp"

class GUIKeybox {
public:

     GUIKeybox(const glm::vec4& destRect, const ColorRGBA8& color, unsigned int value);
     void update(InputManager& manager, std::vector<GUIKeybox>& keyboxes);
     void render(GUIRenderer& renderer);

     unsigned int getValue();

private:

     glm::vec4 m_destRect;
     ColorRGBA8 m_baseColor;
     ColorRGBA8 m_currentColor;
     bool m_isSelected = false;
     unsigned int m_value = 0;



};
