#include "GUISlider.hpp"
#include "Utils.hpp"
#include "Constants.hpp"
#include <iostream>

GUISlider::GUISlider(const glm::vec2& position, float size, const ColorRGBA8& lineColor, const ColorRGBA8& buttonColor){
     m_position = position;
     m_size = size;
     m_lineColor = lineColor;
     m_buttonColor = m_buttonColor;
     m_buttonRect = glm::vec4(position.x, position.y - SLIDER_BUTTON_HEIGHT / 2, SLIDER_BUTTON_WIDTH, SLIDER_BUTTON_HEIGHT + 1);

}

void GUISlider::update(sf::Window& window, InputManager& manager){

     glm::vec2 mousePos = glm::vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

	mousePos.y = SCREEN_HEIGHT - mousePos.y;

     if(Utils::isInside(mousePos, m_buttonRect)){
          m_currentColor = ColorRGBA8(m_buttonColor.r * 0.6f, m_buttonColor.g * 0.6f, m_buttonColor.b * 0.6f, 255);
          if(manager.isKeyDown(sf::Mouse::Left)){
               m_isSelected = true;
               m_currentColor = ColorRGBA8(m_buttonColor.r * 0.4f, m_buttonColor.g * 0.4f, m_buttonColor.b * 0.4f, 255);
          }
     }
     if(!manager.isKeyDown(sf::Mouse::Left)){
          m_isSelected = false;
          m_currentColor = m_buttonColor;
     }

     if(m_isSelected){
          m_buttonRect.x = mousePos.x - SLIDER_BUTTON_WIDTH / 2.0f;
     }

     if(m_buttonRect.x < m_position.x){
          m_buttonRect.x = m_position.x;
     }
     if(m_buttonRect.x > m_position.x + m_size - SLIDER_BUTTON_WIDTH){
          m_buttonRect.x = m_position.x + m_size - SLIDER_BUTTON_WIDTH;
     }

     m_value = (m_buttonRect.x - m_position.x) / ((m_position.x + m_size - SLIDER_BUTTON_WIDTH) - m_position.x);

}

float GUISlider::getValue(){
     return m_value;
}

void GUISlider::render(GUIRenderer& renderer){

     renderer.draw(glm::vec4(m_position, m_size, 1.0f), m_lineColor); //Rendering the line
     renderer.draw(glm::vec4(m_buttonRect), m_currentColor);

}
