#include "PauseMenu.hpp"
#include <iostream>

void PauseMenu::init(InputManager* _manager, Settings* _settings, Game* _game, GUIRenderer* _guiRenderer){
	m_guiRenderer = _guiRenderer;
	m_settings = _settings;
	m_inputManager = _manager;
	m_game = _game;
	m_guiRenderer = _guiRenderer;
}

void PauseMenu::update(GameStates& _state, float deltaTime){
	// Change state back to game if the user presses on escape
	if(m_inputManager->isKeyPressed(sf::Keyboard::Escape)){
		m_game->syncGameWithSettings(m_settings);
		m_inputManager->setMouseGrabbed(true);
		m_inputManager->setMouseVisible(false);
		_state = GameStates::PLAY;
	}
	handleInputs();
}

void PauseMenu::render(){
	m_guiRenderer->drawRect(math::vec4(258, 138, 1404, 804), math::vec4(0, 0, 1, 1), m_guiRenderer->assets.getGrassTexture(), ColorRGBA8());
	m_guiRenderer->drawRect(math::vec4(260, 140, 1400, 800), math::vec4(0, 0, 1, 1), m_guiRenderer->assets.getGrassTexture(), ColorRGBA8(24, 30, 40, 255));
}

void PauseMenu::handleInputs(){

}
