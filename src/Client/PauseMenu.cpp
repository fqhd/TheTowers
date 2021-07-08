#include "PauseMenu.hpp"
#include <iostream>

void PauseMenu::init(InputManager* _manager, GUIFont* _font, Settings* _settings){
	m_settings = _settings;
	m_handler.init(_font, _settings);
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
	float w = m_settings->screenWidth;
	float h = m_settings->screenHeight;

	m_handler.rects.push_back(GUIRect(glm::vec4(w * 0.078, h * 0.075, w * 0.844, h * 0.85), ColorRGBA8(240, 210, 38, 255)));
	m_handler.rects.push_back(GUIRect(glm::vec4(w * 0.08, h * 0.08, w * 0.84, h * 0.84), ColorRGBA8(20, 20, 20, 255)));

	m_handler.labels.push_back(GUILabel("Fog: ", glm::vec2(w * 0.15, h * 0.75), ColorRGBA8(255, 255, 255, 255)));
	m_handler.labels.push_back(GUILabel("SAVE SETTINGS", glm::vec2(w * 0.43, h * 0.13), ColorRGBA8(255, 255, 255, 255)));
	m_handler.checkboxes.push_back(GUICheckbox(glm::vec4(w * 0.215, h * 0.75, w * 0.02, h * 0.032)));

	m_handler.buttons.push_back(GUIButton(glm::vec4(w * 0.4125, h * 0.12, w * 0.175, h * 0.05)));
}
