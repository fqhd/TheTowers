#include "PauseMenu.hpp"
#include "Constants.hpp"

const float MENU_WIDTH = 900.0f;
const float MENU_HEIGHT = 600.0f;
const float MENU_BG_WIDTH = MENU_WIDTH + 2.0f;
const float MENU_BG_HEIGHT = MENU_HEIGHT + 2.0f;

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


void PauseMenu::update(GameStates& state, Settings& settings, Player& player, GUICanvas& workspace){

	// Change state back to game if the user presses on escape
	if(InputManager::isKeyPressed(GLFW_KEY_ESCAPE)){
		Window::setMouseCursorGrabbed(true);
		state = GameStates::PLAY;
	}
	
}
