#include "GUICheckbox.hpp"
#include "Constants.hpp"

GUICheckbox::GUICheckbox(const glm::vec4& destRect, const ColorRGBA8& onColor, const ColorRGBA8& offColor){
     m_destRect = destRect;
     m_onColor = onColor;
     m_offColor = offColor;
}

void GUICheckbox::update(sf::Window& window, InputManager& manager){
     glm::vec2 mousePos = glm::vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

     mousePos.y = SCREEN_HEIGHT - mousePos.y;

     ColorRGBA8 color = m_isChecked ? m_onColor : m_offColor;

     m_currentColor = color;
     if(Utils::isInside(mousePos, m_destRect)){
          m_currentColor = ColorRGBA8(color.r * 0.6f, color.g * 0.6f, color.b * 0.6f, color.a);
          if(manager.isKeyDown(sf::Mouse::Left)){
               m_currentColor = ColorRGBA8(color.r * 0.3f, color.g * 0.3f, color.b * 0.3f, color.a);
          }else if(manager.isKeyReleased(sf::Mouse::Left)){
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
