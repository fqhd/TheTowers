#include "GUICheckbox.hpp"
#include "../../../Constants.hpp"
#include "../Input/Window.hpp"
#include <iostream>


GUICheckbox::GUICheckbox(const glm::vec4 & destRect, const ColorRGBA8 & onColor, const ColorRGBA8 & offColor, bool checked) {
	m_destRect = destRect;
	m_onColor = onColor;
	m_offColor = offColor;
	isChecked = checked;
}

void GUICheckbox::update() {

	ColorRGBA8 color = isChecked ? m_onColor : m_offColor;

	glm::vec2 mousePos = Utils::mapPoint(InputManager::getMousePosition(), glm::vec2(Window::getWidth(), Window::getHeight()), glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT));

	m_currentColor = color;
	if (Utils::isInside(Utils::flipCoords(mousePos, SCREEN_HEIGHT), m_destRect)) {
		m_currentColor = ColorRGBA8(color.r * 0.6f, color.g * 0.6f, color.b * 0.6f, color.a);
		if (InputManager::isButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
			m_currentColor = ColorRGBA8(color.r * 0.3f, color.g * 0.3f, color.b * 0.3f, color.a);
		} else if (InputManager::isButtonReleased(GLFW_MOUSE_BUTTON_LEFT)) {
			isChecked = !isChecked;
		}
	}

}

void GUICheckbox::render(GUIRenderer& renderer) {
	renderer.draw(glm::vec4(m_destRect.x - 1, m_destRect.y - 1, m_destRect.z + 2, m_destRect.z + 2), ColorRGBA8(100, 100, 100, 255));
	renderer.draw(m_destRect, m_currentColor);
}