#pragma once
#include <SFML/Graphics.hpp>
#include "GUIRenderer.hpp"
#include "GUIFontRenderer.hpp"
#include "InputManager.hpp"

class GUISlider {
public:

     GUISlider(const glm::vec2& position, float size, const ColorRGBA8& lineColor, const ColorRGBA8& buttonColor, float value);
     void update(sf::Window& window, InputManager& manager);
     void render(GUIRenderer& renderer);

     float getValue();

private:

     float m_value = 0.0f;
     bool m_isSelected = false;
     glm::vec4 m_buttonRect;
     glm::vec2 m_position;
     float m_size = 0.0f;
     ColorRGBA8 m_lineColor;
     ColorRGBA8 m_buttonColor;
     ColorRGBA8 m_currentColor;

};
