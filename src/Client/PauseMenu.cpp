#include "PauseMenu.hpp"
#include <iostream>

void PauseMenu::init(InputManager* _manager, Settings* _settings, GUIRenderer* _guiRenderer){
	m_guiRenderer = _guiRenderer;
	m_settings = _settings;
	m_inputManager = _manager;
	m_guiRenderer = _guiRenderer;

	initGUI();
}

void PauseMenu::update(GameStates& _state, float deltaTime){
	// Change state back to game if the user presses on escape
	if(m_inputManager->isKeyPressed(GLFW_KEY_ESCAPE)){
		m_inputManager->setMouseGrabbed(true);
		_state = GameStates::PLAY;
	}
	updateGUI(deltaTime);
	syncSettingsWithGUI();
}

void PauseMenu::render(){
	// Background
	m_guiRenderer->drawRect(math::vec4(138, 58, 1004, 604), math::vec4(0, 0, 1, 1), m_guiRenderer->assets.getGrassTexture(), ColorRGBA8());
	m_guiRenderer->drawRect(math::vec4(140, 60, 1000, 600), math::vec4(0, 0, 10, 7), m_guiRenderer->assets.getGrassTexture(), ColorRGBA8(34, 40, 50, 255));

	// Text
	m_guiRenderer->drawText("Fog: ", math::vec2(175, 600), math::vec2(1, 1), ColorRGBA8());
	m_guiRenderer->drawText("Vignette: ", math::vec2(175, 525), math::vec2(1, 1), ColorRGBA8());
	m_guiRenderer->drawText("Debug Mode: ", math::vec2(175, 450), math::vec2(1, 1), ColorRGBA8());
	m_guiRenderer->drawText("Block Outline: ", math::vec2(175, 375), math::vec2(1, 1), ColorRGBA8());

	renderGUI();
}

void PauseMenu::syncSettingsWithGUI(){
	m_settings->isFogToggled = fog.isChecked();
	m_settings->isDebugToggled = debug.isChecked();
	m_settings->isVignetteToggled = vignette.isChecked();
	m_settings->renderOutline = outline.isChecked();
	if(save.isPressed()){
		m_settings->writeToFile();
	}
}

void PauseMenu::initGUI(){
	save.init(math::vec4(440, 80, 400, 50));
	fog.init(math::vec4(600, 600, 48, 48), m_settings->isFogToggled);
	vignette.init(math::vec4(600, 525, 48, 48), m_settings->isVignetteToggled);
	debug.init(math::vec4(600, 450, 48, 48), m_settings->isDebugToggled);
	outline.init(math::vec4(600, 375, 48, 48), m_settings->renderOutline);
}

void PauseMenu::updateGUI(float deltaTime){
	save.update(m_inputManager, deltaTime);
	fog.update(m_inputManager, deltaTime);
	vignette.update(m_inputManager, deltaTime);
	debug.update(m_inputManager, deltaTime);
	outline.update(m_inputManager, deltaTime);
}

void PauseMenu::renderGUI(){
	save.render(m_guiRenderer);
	fog.render(m_guiRenderer);
	vignette.render(m_guiRenderer);
	debug.render(m_guiRenderer);
	outline.render(m_guiRenderer);
}