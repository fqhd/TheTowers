#include "GUIKeybox.hpp"
#include <iostream>

GUIKeybox::GUIKeybox(const glm::vec4& destRect, const ColorRGBA8& color, unsigned int value){
     m_destRect = destRect;
     m_baseColor = color;
     m_value = value;
}

void GUIKeybox::update(InputManager& manager, std::vector<GUIKeybox>& keyboxes){

     m_currentColor = m_baseColor;

     if(manager.getLastKeyPressed() != -1 && m_isSelected){
          m_isSelected = false;
          m_currentColor = m_baseColor;
          m_value = manager.getLastKeyPressed();
          std::cout << m_value << std::endl;
     }

     if(Utils::isInside(manager.getMousePosition(), m_destRect)){
          m_currentColor = ColorRGBA8(m_baseColor.r * 0.6f, m_baseColor.g * 0.6f, m_baseColor.b * 0.6f, 255);
          if(manager.isKeyDown(sf::Mouse::Left)){
               for(auto& i : keyboxes){
                    i.m_isSelected = false;
               }
               m_isSelected = true;
               m_currentColor = ColorRGBA8(m_baseColor.r * 0.4f, m_baseColor.g * 0.4f, m_baseColor.b * 0.4f, 255);
          }
     }

     if(m_isSelected){
          m_currentColor = ColorRGBA8(m_baseColor.r * 0.4f, m_baseColor.g * 0.4f, m_baseColor.b * 0.4f, 255);
     }


}

void GUIKeybox::render(GUIRenderer& renderer){
     renderer.draw(m_destRect, m_currentColor);
}

unsigned int GUIKeybox::getValue(){
     return m_value;
}
