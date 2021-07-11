#include "PauseMenu.hpp"
#include <iostream>

void PauseMenu::init(InputManager* _manager, Settings* _settings, GUICanvas* _canvas, Game* _game){
	m_canvas = _canvas;
	m_settings = _settings;
	m_inputManager = _manager;
	m_game = _game;
	initGUI();
}

void PauseMenu::update(GameStates& _state, float deltaTime){
	// Change state back to game if the user presses on escape
	if(m_inputManager->isKeyPressed(GLFW_KEY_ESCAPE)){
		m_game->syncGameWithSettings(m_settings);
		m_inputManager->setMouseGrabbed(true);
		_state = GameStates::PLAY;
	}

	m_canvas->update(m_inputManager, deltaTime);

	handleInputs();
}

void PauseMenu::render(){
	m_canvas->render();
}

void PauseMenu::destroy(){
}

void PauseMenu::initGUI(){
	// Rects
	m_canvas->rects.push_back(GUIRect(glm::vec4(70, 30, 1140, 630), ColorRGBA8(240, 210, 38, 255), 1)); // Outline
	m_canvas->rects.push_back(GUIRect(glm::vec4(72, 32, 1136, 626), ColorRGBA8(20, 20, 20, 255), 1)); // Background

	// Labels
	m_canvas->labels.push_back(GUILabel("Fog: ", glm::vec2(150, 525), ColorRGBA8(255, 255, 255, 255)));
	m_canvas->labels.push_back(GUILabel("Vignette: ", glm::vec2(150, 475), ColorRGBA8(255, 255, 255, 255)));
	m_canvas->labels.push_back(GUILabel("Debug: ", glm::vec2(150, 425), ColorRGBA8(255, 255, 255, 255)));
	m_canvas->labels.push_back(GUILabel("SAVE SETTINGS", glm::vec2(525, 68), ColorRGBA8(255, 255, 255, 255)));

	// Checkboxes
	m_canvas->checkboxes.push_back(GUICheckbox(glm::vec4(325, 525, 32, 32), m_settings->isFogToggled, 1)); // Fog checkbox
	m_canvas->checkboxes.push_back(GUICheckbox(glm::vec4(325, 475, 32, 32), m_settings->isVignetteToggled, 1)); // Vignette checkbox
	m_canvas->checkboxes.push_back(GUICheckbox(glm::vec4(325, 425, 32, 32), m_settings->isDebugToggled, 1)); // Vignette checkbox

	// Buttons
	m_canvas->buttons.push_back(GUIButton(glm::vec4(500, 58, 240, 38), 1)); // Save Settings Button
}

void PauseMenu::handleInputs(){
	// Write Settings to file
	if(m_canvas->buttons[0].isPressed()){
		m_settings->writeToFile();
	}

	m_settings->isFogToggled = m_canvas->checkboxes[0].isChecked();
	m_settings->isVignetteToggled = m_canvas->checkboxes[1].isChecked();
	m_settings->isDebugToggled = m_canvas->checkboxes[2].isChecked();
}
