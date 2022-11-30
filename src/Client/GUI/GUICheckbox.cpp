#include "GUICheckbox.hpp"
#include <iostream>
#include "GUIUVLoader.hpp"

void GUICheckbox::init(const glm::vec4& destRect, bool _checked) {
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

void GUICheckbox::update(float deltaTime) {
	ColorRGBA8 color = m_isChecked ? m_onColor : m_offColor;
	glm::ivec2 mousePos = glm::floor(InputManager::getScaledMousePosition());

	m_currentColor = color;
	if (Utils::isInside(mousePos, m_destRect)) { // Mouse is inside of checkbox
		m_targetRect = glm::vec4(m_originalRect.x - 6, m_originalRect.y - 6, m_originalRect.z + 12, m_originalRect.w + 12);
		m_currentColor = ColorRGBA8(color.r * 0.6f, color.g * 0.6f, color.b * 0.6f, color.a);
		if (InputManager::isKeyDown(GLFW_MOUSE_BUTTON_LEFT)) {
			m_targetRect = m_originalRect + glm::vec4(-4, -4, 8, 8);
			m_currentColor = ColorRGBA8(color.r * 0.3f, color.g * 0.3f, color.b * 0.3f, color.a);
		} else if (InputManager::isKeyReleased(GLFW_MOUSE_BUTTON_LEFT)) {
			m_isChecked = !m_isChecked;
		}
	}else{ // Mouse is outside of checkbox
		m_targetRect = m_originalRect;
	}

	// Calculating animation delta
	m_destRect += (m_targetRect - m_destRect) * 24.0f * deltaTime;

	// Updating shadow position
	m_shadowRect = m_destRect + glm::vec4(8, -8, 0, 0);
}

void GUICheckbox::render() {
	GUIRenderer::drawRect(m_shadowRect, GUIUVLoader::getUV("White"), ColorRGBA8(0, 0, 0, 128)); // Rendering shadow
	GUIRenderer::drawRect(glm::vec4(m_destRect.x - 1, m_destRect.y - 1, m_destRect.z + 2, m_destRect.w + 2), GUIUVLoader::getUV("White"), ColorRGBA8(20, 20, 20, 255)); // Rendering outline
	GUIRenderer::drawRect(m_destRect, GUIUVLoader::getUV("White"), m_currentColor); // Rendering on/off rect
}

bool GUICheckbox::isChecked(){
	return m_isChecked;
}
