#include "GUICheckbox.hpp"
#include <iostream>


GUICheckbox::GUICheckbox(const glm::vec4 & destRect, const ColorRGBA8 & onColor, const ColorRGBA8 & offColor, bool checked) {
	m_destRect = destRect;
	m_onColor = onColor;
	m_offColor = offColor;
	isChecked = checked;
}

void GUICheckbox::update(InputManager& _manager) {
	ColorRGBA8 color = isChecked ? m_onColor : m_offColor;
	glm::vec2 mousePos = _manager.getScaledMousePosition();

	m_currentColor = color;
	if (Utils::isInside(Utils::flipCoords(mousePos, 720.0f), m_destRect)) {
		m_currentColor = ColorRGBA8(color.r * 0.6f, color.g * 0.6f, color.b * 0.6f, color.a);
		if (_manager.isKeyPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			m_currentColor = ColorRGBA8(color.r * 0.3f, color.g * 0.3f, color.b * 0.3f, color.a);
		} else if (_manager.isKeyReleased(GLFW_MOUSE_BUTTON_LEFT)) {
			isChecked = !isChecked;
		}
	}

}

void GUICheckbox::render(GUIRenderer& renderer) {
	renderer.draw(glm::vec4(m_destRect.x - 1, m_destRect.y - 1, m_destRect.z + 2, m_destRect.z + 2), ColorRGBA8(100, 100, 100, 255));
	renderer.draw(m_destRect, m_currentColor);
}