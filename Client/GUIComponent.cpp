#include "GUIComponent.hpp"
#include "Utils.hpp"
#include <iostream>

GUIComponent::GUIComponent(const glm::vec4& destRect, const ColorRGBA8& color){
     m_destRect = destRect;
     m_baseColor = color;
}

void GUIComponent::update(InputManager& manager, std::vector<GUIComponent>& components){
     m_currentColor = m_baseColor;

     if(m_isSelected){
          m_currentColor = ColorRGBA8(m_baseColor.r * 0.6f, m_baseColor.g * 0.6f, m_baseColor.b * 0.6f, 255);
     }

     if(Utils::isInside(manager.getMousePosition(), m_destRect)){

          m_currentColor = ColorRGBA8(m_baseColor.r * 0.6f, m_baseColor.g * 0.6f, m_baseColor.b * 0.6f, 255);
          if(manager.isMouseDown(sf::Mouse::Left)){
               m_currentColor = ColorRGBA8(m_baseColor.r * 0.4f, m_baseColor.g * 0.4f, m_baseColor.b * 0.4f, 255);
               for(auto& i : components){
                    i.m_isSelected = false;
               }
               m_isSelected = true;
          }
     }



}

void GUIComponent::render(GUIRenderer& renderer){
     renderer.draw(m_destRect, m_currentColor);
}

bool GUIComponent::isSelected(){
     return m_isSelected;
}
