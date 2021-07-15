#include "InputManager.hpp"
#include "../Utils/Utils.hpp"
#include <iostream>


void InputManager::init(sf::Window* _window) {
	m_window = _window;
	m_windowSize.x = m_window->getSize().x;
	m_windowSize.y = m_window->getSize().y;
	m_mousePosition.x = sf::Mouse::getPosition().x;
	m_mousePosition.y = sf::Mouse::getPosition().y;
}

void InputManager::keyPressed(unsigned int _keyID){
	m_keymap[_keyID] = true;
}

void InputManager::keyReleased(unsigned int _keyID){
	m_keymap[_keyID] = false;
}

void InputManager::buttonPressed(unsigned int _buttonID){
	m_buttonmap[_buttonID] = true;
}

void InputManager::buttonReleased(unsigned int _buttonID){
	m_buttonmap[_buttonID] = false;
}

bool InputManager::processInput() {
	m_previousMousePosition = m_mousePosition;
	m_previousKeymap = m_keymap;
	m_previousButtonmap = m_buttonmap;

	while(m_window->pollEvent(m_event)){
		switch(m_event.type){
			case sf::Event::Closed:
				return true;
			break;
			case sf::Event::KeyPressed:
				keyPressed(m_event.key.code);
			break;
			case sf::Event::KeyReleased:
				keyReleased(m_event.key.code);
			break;
			case sf::Event::MouseButtonPressed:
				buttonPressed(m_event.mouseButton.button);
			break;
			case sf::Event::MouseButtonReleased:
				buttonReleased(m_event.mouseButton.button);
			break;
			case sf::Event::MouseMoved:
				m_mousePosition.x = m_event.mouseMove.x;
				m_mousePosition.y = m_event.mouseMove.y;
			break;
			case sf::Event::Resized:
				m_windowSize.x = m_event.size.width;
				m_windowSize.y = m_event.size.height;
			break;
			case sf::Event::LostFocus:
				m_hasFocus = false;
			break;
			case sf::Event::GainedFocus:
				m_hasFocus = true;
			break;
			default:

			break;
		}
	}
	return false;
}

void InputManager::centerMouse(){
	sf::Mouse::setPosition(sf::Vector2i(m_windowSize.x / 2, m_windowSize.y / 2));
	m_mousePosition.x = m_windowSize.x / 2;
	m_mousePosition.y = m_windowSize.y / 2;
}

bool InputManager::hasFocus(){
	return m_hasFocus;
}

void InputManager::setMouseVisible(bool _visible){
	m_window->setMouseCursorVisible(_visible);
}

void InputManager::setMouseGrabbed(bool _grabbed){
	m_window->setMouseCursorGrabbed(_grabbed);
}

void InputManager::setVerticalSync(bool _sync){
	m_window->setVerticalSyncEnabled(_sync);
}

glm::vec2 InputManager::getWindowSize(){
	return m_windowSize;
}

glm::vec2 InputManager::getPreviousMousePosition(){
	return m_previousMousePosition;
}

glm::vec2 InputManager::getMousePosition(){
	return m_mousePosition;
}

glm::vec2 InputManager::getScaledMousePosition(){
	glm::vec2 mousePos = getMousePosition();
	glm::vec2 windowSize = getWindowSize();
	return Utils::mapPoint(glm::vec2(mousePos.x, mousePos.y), glm::vec2(windowSize.x, windowSize.y), glm::vec2(1280.0f, 720.0f));
}

bool InputManager::isKeyDown(int _keyID){
	auto it = m_keymap.find(_keyID);
	if(it != m_keymap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::wasKeyDown(int _keyID){
	auto it = m_previousKeymap.find(_keyID);
	if(it != m_previousKeymap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::isKeyPressed(int _keyID){
	return (isKeyDown(_keyID) && !wasKeyDown(_keyID));
}

bool InputManager::isKeyReleased(int _keyID){
	return (!isKeyDown(_keyID) && wasKeyDown(_keyID));
}


bool InputManager::isButtonDown(int _buttonID){
	auto it = m_buttonmap.find(_buttonID);
	if(it != m_buttonmap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::wasButtonDown(int _buttonID){
	auto it = m_previousButtonmap.find(_buttonID);
	if(it != m_previousButtonmap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::isButtonPressed(int _buttonID){
	return (isButtonDown(_buttonID) && !wasButtonDown(_buttonID));
}

bool InputManager::isButtonReleased(int _buttonID){
	return (!isButtonDown(_buttonID) && wasButtonDown(_buttonID));
}
