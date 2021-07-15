
#include "GUIInput.hpp"

GUIInput::GUIInput(const math::vec4& destRect) {
	m_destRect = destRect;
	m_outlineRect = math::vec4(destRect.x-2, destRect.y-2, destRect.z+4, destRect.w+4);
	m_last_pressed = 0;
}

void GUIInput::update(InputManager* _manager) {
	glm::vec2 mousePos = _manager->getScaledMousePosition();
	time_t time_ = time(NULL);
	if (Utils::isInside(Utils::flipCoords(mousePos, 720.0f), m_destRect)) {
		if (_manager->isKeyDown(GLFW_MOUSE_BUTTON_LEFT)) {
			if (time_-m_last_pressed < 10) {
				m_active = true;
				m_last_pressed = time_;
			}
			printf("pressed\n");
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
