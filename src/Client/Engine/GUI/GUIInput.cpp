
#include "GUIInput.hpp"

GUIInput::GUIInput(const math::vec4& destRect) {
	m_destRect = destRect;
	m_outlineRect = math::vec4(destRect.x-2, destRect.y-2, destRect.z+4, destRect.w+4);
	m_last_pressed = 0;
}

void GUIInput::update(InputManager* _manager) {
	glm::vec2 mousePos = _manager->getScaledMousePosition();
	int64_t time_ = Utils::getTimeMs();
	if (Utils::isInside(Utils::flipCoords(mousePos, 720.0f), m_destRect)) {
		if (_manager->isButtonDown(sf::Mouse::Left)) {
			if (time_-m_last_pressed > 100) {
				m_active = m_active ? false : true;
				m_last_pressed = time_;
			}
		}
	}
}

void GUIInput::render(GUIRenderer* renderer) {
	renderer->draw(m_outlineRect, (m_active ? ColorRGBA8() : ColorRGBA8(120, 120, 120, 255)), 0);
	renderer->draw(m_destRect, ColorRGBA8(50, 50, 50, 255), 0);
}

// int GUIInput::getInt() {
// }
// std::string GUIInput::getString() {
// }
