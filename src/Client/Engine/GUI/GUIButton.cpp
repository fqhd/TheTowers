#include "GUIButton.hpp"
#include "../Utils/Utils.hpp"
#include "../Utils/Vertex.hpp"


GUIButton::GUIButton(const glm::vec4& destRect) {
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
	glm::vec2 mousePos = _manager->getScaledMousePosition();

	if (Utils::isInside(Utils::flipCoords(mousePos, 720.0f), m_destRect)) { // Mouse is inside the button
		m_targetRect = glm::vec4(m_originalRect.x - 10, m_originalRect.y - 10, m_originalRect.z + 20, m_originalRect.w + 20);
		m_currentColor = ColorRGBA8(m_baseColor.r * 0.8f, m_baseColor.g * 0.8f, m_baseColor.b * 0.8f, m_baseColor.a);
		if (_manager->isKeyDown(GLFW_MOUSE_BUTTON_LEFT)) {
			m_targetRect = m_originalRect + glm::vec4(-4, -4, 8, 8);
			m_currentColor = ColorRGBA8(m_baseColor.r * 0.6f, m_baseColor.g * 0.6f, m_baseColor.b * 0.6f, m_baseColor.a);
		} else if (_manager->isKeyReleased(GLFW_MOUSE_BUTTON_LEFT)) {
			m_isPressed = true;
		}
	}else{ // Mouse is not inside the button
		m_targetRect = m_originalRect;
	}

	// Calculating animation delta
	m_destRect += (m_targetRect - m_destRect) * 24.0f * deltaTime;

	// Updating shadow position
	m_shadowRect = m_destRect + glm::vec4(8, -8, 0, 0);

}

void GUIButton::render(GUIRenderer& renderer) {
	renderer.draw(m_shadowRect, ColorRGBA8(0, 0, 0, 128), 0); // Rendering shadow
	renderer.draw(m_destRect, m_currentColor, 0); // Rendering rect
}

bool GUIButton::isPressed() {
	return m_isPressed;
}
