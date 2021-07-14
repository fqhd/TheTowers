
#include "GUIInput.hpp"

GUIInput::GUIInput(const math::vec4& destRect) {
	m_originalRect = destRect;
	m_outlineRect = math::vec4(destRect.x-5, destRect.y-5, destRect.z+5, destRect.w+5);
}

void GUIInput::update(InputManager* _manager) {

}

void GUIInput::render(GUIRenderer* renderer) {
	
}
