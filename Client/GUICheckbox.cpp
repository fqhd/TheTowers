#include "GUICheckbox.hpp"
#include "Constants.hpp"
#include "Window.hpp"
#include <iostream>


GUICheckbox::GUICheckbox(const glm::vec4& destRect, const ColorRGBA8& onColor, const ColorRGBA8& offColor, bool isChecked){
     m_destRect = destRect;
     m_onColor = onColor;
     m_offColor = offColor;
	m_isChecked = isChecked;
}

void GUICheckbox::update(){

     ColorRGBA8 color = m_isChecked ? m_onColor : m_offColor;

     glm::vec2 mousePos = Utils::mapPoint(InputManager::getMousePosition(), glm::vec2(Window::getWidth(), Window::getHeight()), glm::vec2(Constants::getScreenWidth(), Constants::getScreenHeight()));

     m_currentColor = color;
     if(Utils::isInside(Utils::flipCoords(mousePos, Constants::getScreenHeight()), m_destRect)){
          m_currentColor = ColorRGBA8(color.r * 0.6f, color.g * 0.6f, color.b * 0.6f, color.a);
          if(InputManager::isButtonDown(GLFW_MOUSE_BUTTON_LEFT)){
               m_currentColor = ColorRGBA8(color.r * 0.3f, color.g * 0.3f, color.b * 0.3f, color.a);
          }else if(InputManager::isButtonReleased(GLFW_MOUSE_BUTTON_LEFT)){
               m_isChecked = !m_isChecked;
          }
     }

}

void GUICheckbox::render(GUIRenderer& renderer){
     renderer.draw(glm::vec4(m_destRect.x - 1, m_destRect.y - 1, m_destRect.z + 2, m_destRect.z + 2), ColorRGBA8(100, 100, 100, 255));
     renderer.draw(m_destRect, m_currentColor);
}


bool GUICheckbox::isChecked(){
     return m_isChecked;
}
