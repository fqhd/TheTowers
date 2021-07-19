#include "GUIButton.hpp"
#include "../Utils/Utils.hpp"
#include "../Utils/Vertex.hpp"


GUIButton::GUIButton(const math::vec4& destRect) {
	m_baseColor = ColorRGBA8(120, 255, 255, 255);
	m_destRect = destRect;
	m_originalRect = destRect;
	m_shadowRect = destRect;
	m_targetRect = destRect;

	m_shadowRect.x += 8;
	m_shadowRect.y -= 8;
}

void GUIButton::update(InputManager* _manager, float deltaTime) {
	m_currentColor = m_baseColor;
	m_isPressed = false;
	math::ivec2 mousePos = _manager->getMousePosition();

	if (Utils::isInside(mousePos, m_destRect)) { // Mouse is inside the button
		m_targetRect = math::vec4(m_originalRect.x - 10, m_originalRect.y - 10, m_originalRect.z + 20, m_originalRect.w + 20);
		m_currentColor = ColorRGBA8(m_baseColor.r * 0.8f, m_baseColor.g * 0.8f, m_baseColor.b * 0.8f, m_baseColor.a);
		if (_manager->isButtonDown(sf::Mouse::Left)) {
			m_targetRect = m_originalRect + math::vec4(-4, -4, 8, 8);
			m_currentColor = ColorRGBA8(m_baseColor.r * 0.6f, m_baseColor.g * 0.6f, m_baseColor.b * 0.6f, m_baseColor.a);
		} else if (_manager->isButtonReleased(sf::Mouse::Left)) {
			m_isPressed = true;
		}
	}else{ // Mouse is not inside the button
		m_targetRect = m_originalRect;
	}

	// Calculating animation delta
	m_destRect += (m_targetRect - m_destRect) * 24.0f * deltaTime;

	// Updating shadow position
	m_shadowRect = m_destRect + math::vec4(8, -8, 0, 0);
}

void GUIButton::render(GUIRenderer* _renderer) {
	_renderer->drawRect(m_shadowRect, math::vec4(0, 0, 1, 1), _renderer->assets.getBlankTexture(), ColorRGBA8(0, 0, 0, 128)); // Rendering shadow
	_renderer->drawRect(m_destRect, math::vec4(0, 0, 1, 1), _renderer->assets.getBlankTexture(), m_currentColor); // Rendering rect
}

bool GUIButton::isPressed() {
	return m_isPressed;
}
