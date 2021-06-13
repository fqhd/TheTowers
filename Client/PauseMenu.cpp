#include "PauseMenu.hpp"
#include "Constants.hpp"

void PauseMenu::init(GUIFont* font){

	m_handler.init(font);

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


void PauseMenu::update(GameStates& state, Player& player){

	// Change state back to game if the user presses on escape
	if(InputManager::isKeyPressed(GLFW_KEY_ESCAPE)){
		Window::setMouseCursorGrabbed(true);
		state = GameStates::PLAY;
	}

	m_handler.update();

}

void PauseMenu::render(){
	m_handler.render();
}

void PauseMenu::destroy(){
	m_handler.destroy();
}