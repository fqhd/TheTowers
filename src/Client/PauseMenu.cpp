#include "PauseMenu.hpp"
#include <iostream>

void PauseMenu::init(InputManager* _manager, GUIFont* _font){

	m_handler.init(_font);
	m_inputManager = _manager;

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
	if(m_inputManager->isKeyPressed(GLFW_KEY_ESCAPE)){
		m_inputManager->setMouseGrabbed(true);
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