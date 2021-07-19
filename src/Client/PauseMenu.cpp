#include "PauseMenu.hpp"
#include <iostream>

void PauseMenu::init(InputManager* _manager, Settings* _settings, Game* _game, GUIRenderer* _guiRenderer){
	m_guiRenderer = _guiRenderer;
	m_settings = _settings;
	m_inputManager = _manager;
	m_game = _game;
	m_guiRenderer = _guiRenderer;
	initGUI();
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
	// m_guiRenderer->drawRect(math::vec4(0, 0, 100, 100), math::vec4(0, 0, 1, 1), m_guiAssets->getBlankTexture(), 0.0f, ColorRGBA8());
	m_guiRenderer->drawText("The quick brown fox jumped over your lazy ass", math::vec2(110, 110), ColorRGBA8());
}

void PauseMenu::destroy(){
	
}

void PauseMenu::initGUI(){

}

void PauseMenu::handleInputs(){

}
