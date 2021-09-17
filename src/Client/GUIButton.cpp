#include "GUIButton.hpp"
#include "Utils.hpp"
#include "Vertex.hpp"
#include "GUIUVLoader.hpp"


void GUIButton::init(const math::vec4& destRect) {
	m_baseColor = ColorRGBA8(120, 255, 255, 255);
	m_destRect = destRect;
	m_originalRect = destRect;
	m_shadowRect = destRect;
	m_targetRect = destRect;

	m_shadowRect.x += 8;
	m_shadowRect.y -= 8;
}

void GUIButton::update(float deltaTime) {
	m_currentColor = m_baseColor;
	m_isPressed = false;
	math::ivec2 mousePos = math::floor(InputManager::getMousePosition());

	if (Utils::isInside(mousePos, m_destRect)) { // Mouse is inside the button
		m_targetRect = math::vec4(m_originalRect.x - 10, m_originalRect.y - 10, m_originalRect.z + 20, m_originalRect.w + 20);
		m_currentColor = ColorRGBA8(m_baseColor.r * 0.8f, m_baseColor.g * 0.8f, m_baseColor.b * 0.8f, m_baseColor.a);
		if (InputManager::isKeyDown(GLFW_MOUSE_BUTTON_LEFT)) {
			m_targetRect = m_originalRect + math::vec4(-4, -4, 8, 8);
			m_currentColor = ColorRGBA8(m_baseColor.r * 0.6f, m_baseColor.g * 0.6f, m_baseColor.b * 0.6f, m_baseColor.a);
		} else if (InputManager::isKeyReleased(GLFW_MOUSE_BUTTON_LEFT)) {
			m_isPressed = true;
		}
	}else{ // Mouse is not inside the button
		m_targetRect = m_originalRect;
	}

	// Animation
	m_destRect += (m_targetRect - m_destRect) * 24.0f * deltaTime;

	// Updating shadow position
	m_shadowRect = m_destRect + math::vec4(8, -8, 0, 0);
}

void GUIButton::render() {
	GUIRenderer::drawRect(m_shadowRect, GUIUVLoader::getUV("White"), ColorRGBA8(0, 0, 0, 128)); // Rendering shadow
	GUIRenderer::drawRect(m_destRect, GUIUVLoader::getUV("White"), m_currentColor); // Rendering rect
}

bool GUIButton::isPressed() {
	return m_isPressed;
}
