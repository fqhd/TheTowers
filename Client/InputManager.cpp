#include "InputManager.hpp"

void InputManager::processInput(sf::Window& window){

	m_previousKeyMap = m_keymap;
	m_previousMouseMap = m_mousemap;
	m_lastKeyTyped = 0;
	m_lastKeyPressed = -1;

	while(window.pollEvent(m_event)){
		switch(m_event.type){
		case sf::Event::Closed:
			m_isCloseRequested = true;
		break;
		case sf::Event::KeyPressed:
			m_lastKeyPressed = m_event.key.code;
			keyPressed(m_event.key.code);
		break;
		case sf::Event::KeyReleased:
			keyReleased(m_event.key.code);
		break;
		case sf::Event::MouseButtonPressed:
			mousePressed(m_event.mouseButton.button);
		break;
		case sf::Event::MouseButtonReleased:
			mouseReleased(m_event.mouseButton.button);
		break;
		case sf::Event::TextEntered:
			m_lastKeyTyped = static_cast<char>(m_event.text.unicode);
		break;
		case sf::Event::MouseMoved:
			m_mousePosition = glm::vec2(m_event.mouseMove.x, window.getSize().y - m_event.mouseMove.y);
		break;
		}
	}

}

const glm::vec2& InputManager::getMousePosition(){
	return m_mousePosition;
}

bool InputManager::isCloseRequested(){
	return m_isCloseRequested;
}

bool InputManager::isKeyPressed(unsigned int keyID){
	return (isKeyDown(keyID) && !wasKeyDown(keyID));
}

bool InputManager::isKeyReleased(unsigned int keyID){
	return (!isKeyDown(keyID) && wasKeyDown(keyID));
}

bool InputManager::isMousePressed(unsigned int keyID){
	return (isMouseDown(keyID) && !wasMouseDown(keyID));
}

bool InputManager::isMouseReleased(unsigned int keyID){
	return (!isMouseDown(keyID) && wasMouseDown(keyID));
}


bool InputManager::isKeyDown(unsigned int keyID){
	auto it = m_keymap.find(keyID);
	if(it != m_keymap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::isMouseDown(unsigned int buttonID){
	auto it = m_mousemap.find(buttonID);
	if(it != m_mousemap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::wasKeyDown(unsigned int buttonID){
	auto it = m_previousKeyMap.find(buttonID);
	if(it != m_previousKeyMap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::wasMouseDown(unsigned int buttonID){
	auto it = m_previousMouseMap.find(buttonID);
	if(it != m_previousMouseMap.end()){
		return it->second;
	}
	return false;
}

void InputManager::mousePressed(unsigned int buttonID){
	m_mousemap[buttonID] = true;
}

void InputManager::mouseReleased(unsigned int buttonID){
	m_mousemap[buttonID] = false;
}

void InputManager::keyPressed(unsigned int keyID){
	m_keymap[keyID] = true;
}

void InputManager::keyReleased(unsigned int keyID){
	m_keymap[keyID] = false;
}

char InputManager::getLastKeyPressed(){
	return m_lastKeyPressed;
}

char InputManager::getLastKeyTyped(){
	return m_lastKeyTyped;
}
