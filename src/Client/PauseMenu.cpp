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
		m_inputManager->setMouseVisible(false);
		m_inputManager->centerMouse();
		_state = GameStates::PLAY;
	}
	updateGUI(deltaTime);
	syncSettingsWithGUI();
}

void PauseMenu::render(){
	// Background
	m_guiRenderer->drawRect(math::vec4(258, 138, 1404, 804), math::vec4(0, 0, 1, 1), m_guiRenderer->assets.getGrassTexture(), ColorRGBA8());
	m_guiRenderer->drawRect(math::vec4(260, 140, 1400, 800), math::vec4(0, 0, 10, 7), m_guiRenderer->assets.getGrassTexture(), ColorRGBA8(34, 40, 50, 255));

	// Text
	m_guiRenderer->drawText("Fog: ", math::vec2(325, 800), ColorRGBA8());
	m_guiRenderer->drawText("Vignette: ", math::vec2(325, 700), ColorRGBA8());
	m_guiRenderer->drawText("Debug Mode: ", math::vec2(325, 600), ColorRGBA8());

	renderGUI();
}

void PauseMenu::syncSettingsWithGUI(){
	m_settings->isFogToggled = fog.isChecked();
	m_settings->isDebugToggled = debug.isChecked();
	m_settings->isVignetteToggled = vignette.isChecked();
	if(save.isPressed()){
		m_settings->writeToFile();
	}
}

void PauseMenu::initGUI(){
	save.init(math::vec4(760, 175, 400, 50));
	fog.init(math::vec4(700, 800, 48, 48), m_settings->isFogToggled);
	vignette.init(math::vec4(700, 700, 48, 48), m_settings->isVignetteToggled);
	debug.init(math::vec4(700, 600, 48, 48), m_settings->isDebugToggled);
}

void PauseMenu::updateGUI(float deltaTime){
	save.update(m_inputManager, deltaTime);
	fog.update(m_inputManager, deltaTime);
	vignette.update(m_inputManager, deltaTime);
	debug.update(m_inputManager, deltaTime);
}

void PauseMenu::renderGUI(){
	save.render(m_guiRenderer);
	fog.render(m_guiRenderer);
	vignette.render(m_guiRenderer);
	debug.render(m_guiRenderer);
}