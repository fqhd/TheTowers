#include "GUIButton.hpp"
#include "../Utils/Utils.hpp"
#include "../../../Constants.hpp"
#include "../Utils/Vertex.hpp"


GUIButton::GUIButton(const glm::vec4& destRect, const ColorRGBA8& color) {
	m_destRect = destRect;
	m_baseColor = color;
}

void GUIButton::update(InputManager& _manager) {
	m_currentColor = m_baseColor;
	m_isPressed = false;
	glm::vec2 mousePos = _manager.getScaledMousePosition();

	if (Utils::isInside(Utils::flipCoords(mousePos, 720.0f), m_destRect)) {
		m_currentColor = ColorRGBA8(m_baseColor.r * 0.8f, m_baseColor.g * 0.8f, m_baseColor.b * 0.8f, m_baseColor.a);
		if (_manager.isButtonDown(sf::Mouse::Left)) {
			m_currentColor = ColorRGBA8(m_baseColor.r * 0.6f, m_baseColor.g * 0.6f, m_baseColor.b * 0.6f, m_baseColor.a);
		} else if (_manager.isButtonReleased(sf::Mouse::Left)) {
			m_isPressed = true;
		}
	}


}

void GUIButton::render(GUIRenderer& renderer) {
	renderer.draw(m_destRect, m_currentColor);
}

bool GUIButton::isPressed() {
	return m_isPressed;
}