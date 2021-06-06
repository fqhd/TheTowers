#include "GUIKeybox.hpp"
#include "Window.hpp"
#include "Constants.hpp"


GUIKeybox::GUIKeybox(const glm::vec4& destRect, const ColorRGBA8& color, unsigned int v){
  m_destRect = destRect;
  m_baseColor = color;
  value = v;
}

void GUIKeybox::update(std::vector<GUIKeybox>& keyboxes){
  glm::vec2 mousePos = Utils::mapPoint(InputManager::getMousePosition(), glm::vec2(Window::getWidth(), Window::getHeight()), glm::vec2(Constants::getScreenWidth(), Constants::getScreenHeight()));

  m_currentColor = m_baseColor;

  if(InputManager::getLastKeyPressed() != -1 && m_isSelected){
    m_isSelected = false;
    m_currentColor = m_baseColor;
    value = InputManager::getLastKeyPressed();
  }

  if(Utils::isInside(Utils::flipCoords(mousePos, Constants::getScreenHeight()), m_destRect)){
    m_currentColor = ColorRGBA8(m_baseColor.r * 0.6f, m_baseColor.g * 0.6f, m_baseColor.b * 0.6f, 255);
    if(InputManager::isButtonDown(GLFW_MOUSE_BUTTON_LEFT)){
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
