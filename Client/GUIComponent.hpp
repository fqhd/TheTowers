#pragma once
#include <glm/glm.hpp>
#include "Vertex.hpp"
#include "InputManager.hpp"
#include "GUIRenderer.hpp"

class GUIComponent {
public:

     GUIComponent(const glm::vec4& destRect, const ColorRGBA8& color);
     void update(std::vector<GUIComponent>& components);
     void render(GUIRenderer& renderer);
     bool isSelected();

private:

     glm::vec4 m_destRect;
     ColorRGBA8 m_baseColor;
     ColorRGBA8 m_currentColor;
     bool m_isSelected = false;

};
