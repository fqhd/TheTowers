#include "InputManager.hpp"
#include "../Utils/Utils.hpp"
#include <iostream>


void InputManager::init(sf::Window * _window) {
	m_window = _window;
}

bool InputManager::processInput() {
	m_previousKeyMap = m_keymap;
	m_previousMouseMap = m_mousemap;

	while(m_window->pollEvent(m_event)){
		if(m_event.type == sf::Event::Closed){
			std::cout << "Closing Game..." << std::endl;
			return true;
		} else if (m_event.type == sf::Event::KeyPressed){
			keyPressed(m_event.key.code);
		} else if (m_event.type == sf::Event::KeyReleased){
			keyReleased(m_event.key.code);
		} else if (m_event.type == sf::Event::MouseButtonPressed){
			buttonPressed(m_event.mouseButton.button);
		} else if (m_event.type == sf::Event::MouseButtonReleased){
			buttonReleased(m_event.mouseButton.button);
		} else if (m_event.type == sf::Event::KeyPressed){
			m_deltaMouseWheel = m_event.mouseWheelScroll.delta;
		}
	}
	return false;
}

glm::vec2 InputManager::getScaledMousePosition(){
	sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
	sf::Vector2u windowSize = m_window->getSize();
	return Utils::mapPoint(glm::vec2(mousePos.x, mousePos.y), glm::vec2(windowSize.x, windowSize.y), glm::vec2(1280.0f, 720.0f));
}

void InputManager::centerMouseInWindow() {
	sf::Vector2u size = m_window->getSize();
	sf::Mouse::setPosition(sf::Vector2i(size.x / 2, size.y / 2), *m_window);
}

float InputManager::getDeltaMouseWheel() {
	return m_deltaMouseWheel;
}

bool InputManager::isKeyPressed(unsigned int keyID) {
	return (isKeyDown(keyID) && !wasKeyDown(keyID));
}

bool InputManager::isKeyReleased(unsigned int keyID) {
	return (!isKeyDown(keyID) && wasKeyDown(keyID));
}

bool InputManager::isButtonPressed(unsigned int keyID) {
	return (isButtonDown(keyID) && !wasButtonDown(keyID));
}

bool InputManager::isButtonReleased(unsigned int keyID) {
	return (!isButtonDown(keyID) && wasButtonDown(keyID));
}

bool InputManager::isButtonDown(unsigned int buttonID) {
	auto it = m_mousemap.find(buttonID);
	if (it != m_mousemap.end()) {
		return it -> second;
	}
	return false;
}

bool InputManager::isKeyDown(unsigned int keyID) {
	auto it = m_keymap.find(keyID);
	if (it != m_keymap.end()) {
		return it -> second;
	}
	return false;
}


bool InputManager::wasKeyDown(unsigned int buttonID) {
	auto it = m_previousKeyMap.find(buttonID);
	if (it != m_previousKeyMap.end()) {
		return it -> second;
	}
	return false;
}

bool InputManager::wasButtonDown(unsigned int buttonID) {
	auto it = m_previousMouseMap.find(buttonID);
	if (it != m_previousMouseMap.end()) {
		return it -> second;
	}
	return false;
}

void InputManager::buttonPressed(unsigned int buttonID) {
	m_mousemap[buttonID] = true;
}

void InputManager::buttonReleased(unsigned int buttonID) {
	m_mousemap[buttonID] = false;
}

void InputManager::keyPressed(unsigned int keyID) {
	m_keymap[keyID] = true;
}

void InputManager::keyReleased(unsigned int keyID) {
	m_keymap[keyID] = false;
}
