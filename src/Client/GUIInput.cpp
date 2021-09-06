#include "GUIInput.hpp"


void GUIInput::init(const math::vec4& destRect,
				   	const ColorRGBA8& backgroundColor, 
	          		const ColorRGBA8& outlineColor, 
			  		const ColorRGBA8& activeOutlineColor) {
						  
	m_outlineRect = math::vec4(destRect.x-5, destRect.y-5, destRect.z+10, destRect.w+10);
	m_destRect = destRect;
	m_onFocus = false;
	m_input = "";

	m_backgroundColor = backgroundColor;
	m_outlineColor = outlineColor;
	m_activeOutlineColor = activeOutlineColor;
}

void GUIInput::update(InputManager* _manager) {
	math::ivec2 mousePos = math::floor(_manager->getMousePosition());
	if (_manager->isKeyPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		if (Utils::isInside(mousePos, m_destRect)) {
			m_onFocus = m_onFocus ? false : true;
		}
		else {
			m_onFocus = false;
		}
	}
	if (m_onFocus) {
		char ascii_key = _manager->getLastKeyPressed();
		if (ascii_key <= -2 && m_input.length() > 0) {
			m_input.pop_back();
		}
		else if (ascii_key > 0) {
			m_input.push_back(ascii_key);
		}
	}
	m_wasSubmitted = m_onFocus && _manager->isKeyPressed(GLFW_KEY_ENTER);
}

bool GUIInput::wasSubmitted() {
	return m_wasSubmitted;
}

std::string GUIInput::getText() {
	return m_input;
}

void GUIInput::focus() {
	m_onFocus = true;
}

void GUIInput::render(GUIRenderer* _renderer) {
	ColorRGBA8 outlineColor = m_onFocus ? m_activeOutlineColor : m_outlineColor;
	_renderer->drawRect(m_outlineRect, math::vec4(0, 0, 1, 1), _renderer->assets.getTexture("blank"), outlineColor);
	_renderer->drawRect(m_destRect, math::vec4(0, 0, 1, 1), _renderer->assets.getTexture("blank"), m_backgroundColor);
	_renderer->drawText(m_input, math::vec2(m_destRect.x + 3, m_destRect.y + 5), math::vec2(0.75, 0.75), ColorRGBA8());	
}