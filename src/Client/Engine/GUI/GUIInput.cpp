
#include "GUIInput.hpp"

GUIInput::GUIInput(const math::vec4& destRect) {
	m_destRect = destRect;
	m_outlineRect = math::vec4(destRect.x-2, destRect.y-2, destRect.z+4, destRect.w+4);

	// fill vector with all keys that are needed i.e
	// 0-25 (abc) 26-35 (number) 
	// XXX add more keys
	supported_keys = std::vector<int>(36);
	std::iota(supported_keys.begin(), supported_keys.end(), 0);

	supported_keys.push_back(sf::Keyboard::Comma);
	supported_keys.push_back(sf::Keyboard::Period);
	supported_keys.push_back(sf::Keyboard::Space);
	supported_keys.push_back(sf::Keyboard::Backspace);
}

void GUIInput::update(InputManager* _manager) {
	glm::vec2 mousePos = _manager->getScaledMousePosition();
	if (Utils::isInside(Utils::flipCoords(mousePos, 720.0f), m_destRect)) {
		if (_manager->isButtonPressed(sf::Mouse::Left)) {
			m_focused = m_focused ? false : true;
		}
	}
	
	// handle key presses when focues
	if (m_focused) {
		sf::Keyboard::Key keyid = sf::Keyboard::Unknown;
		for (int key : supported_keys) {
			if (_manager->isKeyPressed(key)) {
					keyid = (sf::Keyboard::Key)key;
					break;
				}
		}
		if (keyid == -1) return; // no key was pressed
		if (keyid < 26) {
			m_input += (char)(keyid+97);
		}
		else if (keyid > 25 && keyid < 36) {
			m_input += std::to_string(keyid-26);
		}	
		else {
			switch (keyid) {
				case sf::Keyboard::Comma:
					m_input += ',';
				case sf::Keyboard::Period:
					m_input += '.';
				case sf::Keyboard::Space:
					m_input += ' ';
				case sf::Keyboard::Backspace:
					m_input = m_input.substr(0, m_input.size()-1); // remove last char
				default:
					break;
			}
		}

		printf("current input %s\n", m_input.c_str());
	}
}

void GUIInput::render(GUIRenderer* renderer) {
	renderer->draw(m_outlineRect, (m_focused ? ColorRGBA8() : ColorRGBA8(100, 100, 100, 255)), 0);
	renderer->draw(m_destRect, ColorRGBA8(50, 50, 50, 255), 0);
}

// int GUIInput::getInt() {
// }
// std::string GUIInput::getString() {
// }
