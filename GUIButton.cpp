#include "GUIButton.hpp"
#include "Utils.hpp"
#include "Constants.hpp"

GUIButton::GUIButton(const glm::vec4& destRect, const ColorRGBA8& color){
	m_destRect = destRect;
	m_baseColor = color;
}

void GUIButton::update(sf::Window& window, InputManager& manager){

	m_currentColor = m_baseColor;
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	mousePos.y = SCREEN_HEIGHT - mousePos.y;

	if(Utils::isInside(glm::vec2(mousePos.x, mousePos.y), m_destRect)){
		m_currentColor = ColorRGBA8(m_baseColor.r * 0.8f, m_baseColor.g * 0.8f, m_baseColor.b * 0.8f, m_baseColor.a);
		if(manager.isKeyDown(sf::Mouse::Left)){
			m_currentColor = ColorRGBA8(m_baseColor.r * 0.6f, m_baseColor.g * 0.6f, m_baseColor.b * 0.6f, m_baseColor.a);
		}
	}


}

void GUIButton::render(GUIRenderer& renderer){
	renderer.draw(m_destRect, m_currentColor);
}

bool GUIButton::isPressed(){
	return m_isPressed;
}
