#include "GUIButton.hpp"
#include "../Utils/Utils.hpp"
#include "../../../Constants.hpp"
#include "../Input/Window.hpp"
#include "../Utils/Vertex.hpp"


GUIButton::GUIButton(const glm::vec4& destRect, const ColorRGBA8& color) {
	m_destRect = destRect;
	m_baseColor = color;
}

void GUIButton::update() {
	m_currentColor = m_baseColor;
	m_isPressed = false;
	glm::vec2 mousePos = Utils::mapPoint(InputManager::getMousePosition(), glm::vec2(Window::getWidth(), Window::getHeight()), glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT));

	if (Utils::isInside(Utils::flipCoords(mousePos, SCREEN_HEIGHT), m_destRect)) {
		m_currentColor = ColorRGBA8(m_baseColor.r * 0.8f, m_baseColor.g * 0.8f, m_baseColor.b * 0.8f, m_baseColor.a);
		if (InputManager::isButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
			m_currentColor = ColorRGBA8(m_baseColor.r * 0.6f, m_baseColor.g * 0.6f, m_baseColor.b * 0.6f, m_baseColor.a);
		} else if (InputManager::isButtonReleased(GLFW_MOUSE_BUTTON_LEFT)) {
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