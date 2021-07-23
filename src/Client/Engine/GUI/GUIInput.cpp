#include "GUIInput.hpp"


void GUIInput::init(const math::vec4& destRect) {
	m_outlineRect = math::vec4(destRect.x-5, destRect.y-5, destRect.z+10, destRect.w+10);
	m_destRect = destRect;
	m_onFocus = false;

	m_supported_keys = std::vector<int>(36);
    std::iota(m_supported_keys.begin(), m_supported_keys.end(), 0);

    m_supported_keys.push_back(sf::Keyboard::Comma);
    m_supported_keys.push_back(sf::Keyboard::Period);
    m_supported_keys.push_back(sf::Keyboard::Space);
    m_supported_keys.push_back(sf::Keyboard::Backspace);
}

void GUIInput::update(InputManager* _manager) {
	math::ivec2 mousePos = _manager->getMousePosition();
	if (_manager->isButtonPressed(sf::Mouse::Left)) {
		if (Utils::isInside(mousePos, m_destRect)) {
			m_onFocus = m_onFocus ? false : true;
		}
		else {
			m_onFocus = false;
		}
	}
	if (m_onFocus) {
		// handle key presses when focues
        sf::Keyboard::Key keyid = sf::Keyboard::Unknown;
        for (int key : m_supported_keys) {
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
					break;
                case sf::Keyboard::Period:
                    m_input += '.';
					break;
                case sf::Keyboard::Space:
					m_input += ' ';
					break;
                case sf::Keyboard::Backspace:
                    if (m_input.size() > 0) {m_input.pop_back();}
					break;
                default:
                    break;
            }
        }
	}
}

void GUIInput::render(GUIRenderer* _renderer) {
	_renderer->drawRect(m_outlineRect, math::vec4(0, 0, 1, 1), _renderer->assets.getBlankTexture(), 
	m_onFocus ? ColorRGBA8() : ColorRGBA8(200, 200, 200, 255));
	_renderer->drawRect(m_destRect, math::vec4(0, 0, 1, 1), _renderer->assets.getBlankTexture(), ColorRGBA8(150, 150, 150, 255));
	_renderer->drawText(m_input, math::vec2(m_destRect.x + 3, m_destRect.y + 5), math::vec2(0.75, 0.75), ColorRGBA8());
}