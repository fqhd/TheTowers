#include "GUICheckbox.hpp"
#include <iostream>


GUICheckbox::GUICheckbox(const math::vec4& destRect, bool _checked, unsigned int _layer) {
	layer = _layer;
	m_onColor = ColorRGBA8(0, 255, 0, 255);
	m_offColor = ColorRGBA8(255, 0, 0, 255);
	m_isChecked = _checked;

	m_destRect = destRect;
	m_originalRect = destRect;
	m_shadowRect = destRect;
	m_targetRect = destRect;

	m_shadowRect.x += 8;
	m_shadowRect.y -= 8;
}

void GUICheckbox::update(InputManager* _manager, float deltaTime) {
	ColorRGBA8 color = m_isChecked ? m_onColor : m_offColor;
	math::ivec2 mousePos = _manager->getMousePosition();

	m_currentColor = color;
	if (Utils::isInside(mousePos, m_destRect)) { // Mouse is inside of checkbox
		m_targetRect = math::vec4(m_originalRect.x - 10, m_originalRect.y - 10, m_originalRect.z + 20, m_originalRect.w + 20);
		m_currentColor = ColorRGBA8(color.r * 0.6f, color.g * 0.6f, color.b * 0.6f, color.a);
		if (_manager->isButtonDown(sf::Mouse::Left)) {
			m_targetRect = m_originalRect + math::vec4(-4, -4, 8, 8);
			m_currentColor = ColorRGBA8(color.r * 0.3f, color.g * 0.3f, color.b * 0.3f, color.a);
		} else if (_manager->isButtonReleased(sf::Mouse::Left)) {
			m_isChecked = !m_isChecked;
		}
	}else{ // Mouse is outside of checkbox
		m_targetRect = m_originalRect;
	}

	// Calculating animation delta
	m_destRect += (m_targetRect - m_destRect) * 24.0f * deltaTime;

	// Updating shadow position
	m_shadowRect = m_destRect + math::vec4(8, -8, 0, 0);
}

void GUICheckbox::render(GUIRenderer* renderer) {
	renderer->draw(m_shadowRect, ColorRGBA8(0, 0, 0, 128), layer); // Rendering shadow
	renderer->draw(math::vec4(m_destRect.x - 1, m_destRect.y - 1, m_destRect.z + 2, m_destRect.w + 2), ColorRGBA8(100, 100, 100, 255), layer); // Rendering outline
	renderer->draw(m_destRect, m_currentColor, layer); // Rendering on/off rect
}

bool GUICheckbox::isChecked(){
	return m_isChecked;
}
