#include "PauseMenu.hpp"
#include <iostream>

void PauseMenu::init(InputManager* _manager, GUIFont* _font){
	m_handler.init(_font);
	m_inputManager = _manager;
	initGUI();
}

void PauseMenu::update(GameStates& _state, float deltaTime){
	// Change state back to game if the user presses on escape
	if(m_inputManager->isKeyPressed(GLFW_KEY_ESCAPE)){
		m_inputManager->setMouseGrabbed(true);
		_state = GameStates::PLAY;
	}

	m_handler.update(m_inputManager, deltaTime);
}

void PauseMenu::render(){
	m_handler.render();
}

void PauseMenu::destroy(){
	m_handler.destroy();
}

void PauseMenu::initGUI(){
	m_handler.rects.push_back(GUIRect(glm::vec4(0, 0, 200, 200), ColorRGBA8()));
	m_handler.buttons.push_back(GUIButton(glm::vec4(100, 100, 200, 30)));
	m_handler.checkboxes.push_back(GUICheckbox(glm::vec4(100, 200, 200, 30)));
	m_handler.labels.push_back(GUILabel("THIS IS THE CODING TRAIN EXAMPLE", glm::vec2(200, 200), ColorRGBA8(255, 255, 255, 255)));
}
