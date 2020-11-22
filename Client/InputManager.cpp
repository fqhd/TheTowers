#include "InputManager.hpp"

void InputManager::processInput(sf::Window& window){

	m_previousKeyMap = m_keymap;
	m_character = 0;

	while(window.pollEvent(m_event)){
		switch(m_event.type){
		case sf::Event::Closed:
			m_isCloseRequested = true;
		break;
		case sf::Event::KeyPressed:
			keyPressed(m_event.key.code);
		break;
		case sf::Event::KeyReleased:
			keyReleased(m_event.key.code);
		break;
		case sf::Event::MouseButtonPressed:
			keyPressed(m_event.mouseButton.button);
		break;
		case sf::Event::MouseButtonReleased:
			keyReleased(m_event.mouseButton.button);
		break;
		case sf::Event::TextEntered:
			m_character = static_cast<char>(m_event.text.unicode);
		break;
		}
	}

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

bool InputManager::isKeyDown(unsigned int keyID){
	auto it = m_keymap.find(keyID);
	if(it != m_keymap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::wasKeyDown(unsigned int keyID){
	auto it = m_previousKeyMap.find(keyID);
	if(it != m_previousKeyMap.end()){
		return it->second;
	}


	return false;
}

void InputManager::keyPressed(unsigned int keyID){
	m_keymap[keyID] = true;
}

void InputManager::keyReleased(unsigned int keyID){
	m_keymap[keyID] = false;
}

char InputManager::getLastKeyPressed(){
	return m_character;
}
