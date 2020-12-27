#include "GUISlider.hpp"
#include "Utils.hpp"
#include "Constants.hpp"
#include "Window.hpp"


GUISlider::GUISlider(const glm::vec2& position, float size, const ColorRGBA8& lineColor, const ColorRGBA8& buttonColor, float value){
     m_position = position;
     m_size = size;
     m_lineColor = lineColor;
     m_buttonColor = buttonColor;
     m_buttonRect = glm::vec4(position.x, position.y - SLIDER_BUTTON_HEIGHT / 2, SLIDER_BUTTON_WIDTH, SLIDER_BUTTON_HEIGHT + 1);
     m_buttonRect.x += value * size;

}

void GUISlider::update(){

     m_currentColor = m_buttonColor;

     if(Utils::isInside(Utils::flipCoords(InputManager::getMousePosition(), Window::getHeight()), m_buttonRect)){
          m_currentColor = ColorRGBA8(m_buttonColor.r * 0.6f, m_buttonColor.g * 0.6f, m_buttonColor.b * 0.6f, 255);
          if(InputManager::isButtonDown(GLFW_MOUSE_BUTTON_LEFT)){
               m_isSelected = true;
               m_currentColor = ColorRGBA8(m_buttonColor.r * 0.4f, m_buttonColor.g * 0.4f, m_buttonColor.b * 0.4f, 255);
          }
     }

     if(!InputManager::isButtonDown(GLFW_MOUSE_BUTTON_LEFT)){
          m_isSelected = false;
     }


     if(m_isSelected){
          m_buttonRect.x = InputManager::getMousePosition().x - SLIDER_BUTTON_WIDTH / 2.0f;
          m_currentColor = ColorRGBA8(m_buttonColor.r * 0.4f, m_buttonColor.g * 0.4f, m_buttonColor.b * 0.4f, 255);
     }

     if(m_buttonRect.x < m_position.x){
          m_buttonRect.x = m_position.x;
     }
     if(m_buttonRect.x > m_position.x + m_size - SLIDER_BUTTON_WIDTH){
          m_buttonRect.x = m_position.x + m_size - SLIDER_BUTTON_WIDTH;
     }

     m_value = ((m_buttonRect.x - m_position.x)) / ((m_position.x + m_size - SLIDER_BUTTON_WIDTH) - m_position.x);

}

float GUISlider::getValue(){
     return m_value;
}

void GUISlider::render(GUIRenderer& renderer){

     renderer.draw(glm::vec4(m_position, m_size, 1.0f), m_lineColor); //Rendering the line
     renderer.draw(glm::vec4(m_buttonRect), m_currentColor);

}
