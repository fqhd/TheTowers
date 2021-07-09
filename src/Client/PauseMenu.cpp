#include "PauseMenu.hpp"
#include <iostream>

void PauseMenu::init(InputManager* _manager, GUIFont* _font, Settings* _settings, TextureArray* _textureArray){
	m_settings = _settings;
	m_handler.init(_font, _textureArray);
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

	handleInputs();
}

void PauseMenu::render(){
	m_handler.render();
}

void PauseMenu::destroy(){
	m_handler.destroy();
}

void PauseMenu::initGUI(){
	// Rects
	m_handler.rects.push_back(GUIRect(glm::vec4(70, 30, 1140, 630), ColorRGBA8(240, 210, 38, 255), 1)); // Outline
	m_handler.rects.push_back(GUIRect(glm::vec4(72, 32, 1136, 626), ColorRGBA8(20, 20, 20, 255), 1)); // Background

	// Labels
	m_handler.labels.push_back(GUILabel("Fog: ", glm::vec2(150, 525), ColorRGBA8(255, 255, 255, 255)));
	m_handler.labels.push_back(GUILabel("SAVE SETTINGS", glm::vec2(525, 68), ColorRGBA8(255, 255, 255, 255)));

	// Checkboxes
	m_handler.checkboxes.push_back(GUICheckbox(glm::vec4(250, 525, 32, 32), m_settings->isFogToggled, 1)); // Fog checkbox

	// Buttons
	m_handler.buttons.push_back(GUIButton(glm::vec4(500, 58, 240, 38), 1)); // Save Settings Button
}

void PauseMenu::handleInputs(){
	// Write Settings to file
	if(m_handler.buttons[0].isPressed()){
		m_settings->writeToFile();
	}

	m_settings->isFogToggled = m_handler.checkboxes[0].isChecked();
}
