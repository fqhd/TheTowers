#include "PauseMenu.hpp"
#include <iostream>

void PauseMenu::init(InputManager* _manager, sf::Window* _window, GUIFont* font){

	m_handler.init(font);
	m_manager = _manager;
	m_window = _window;

	addImages();
	addCheckboxes();
	addText();

}

void PauseMenu::addText(){

}

void PauseMenu::addImages(){

}

void PauseMenu::addCheckboxes(){

}


void PauseMenu::update(GameStates& _state){

	// Change state back to game if the user presses on escape
	if(m_manager->isKeyPressed(sf::Keyboard::Escape)){
		// m_window->setMouseCursorGrabbed(true);
		// m_window->setMouseCursorVisible(false);
		_state = GameStates::PLAY;
	}

	m_handler.update();

}

void PauseMenu::render(){
	m_handler.render();
}

void PauseMenu::destroy(){
	m_handler.destroy();
}