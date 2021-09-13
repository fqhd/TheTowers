#include "PauseMenu.hpp"
#include <iostream>

void PauseMenu::init(InputManager* _manager, Settings* _settings){
	m_settings = _settings;
	m_inputManager = _manager;
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
	GUIRenderer::drawRect(math::vec4(138, 58, 1004, 604), GUIUVLoader::getUV("White"), ColorRGBA8());
	GUIRenderer::drawRect(math::vec4(140, 60, 1000, 600), GUIUVLoader::getUV("White"), ColorRGBA8(34, 40, 50, 255));

	// Text
	GUIRenderer::drawText("Fog: ", math::vec2(175, 600), math::vec2(1, 1), ColorRGBA8());
	GUIRenderer::drawText("Vignette: ", math::vec2(175, 525), math::vec2(1, 1), ColorRGBA8());
	GUIRenderer::drawText("Debug Mode: ", math::vec2(175, 450), math::vec2(1, 1), ColorRGBA8());
	GUIRenderer::drawText("Block Outline: ", math::vec2(175, 375), math::vec2(1, 1), ColorRGBA8());
	GUIRenderer::drawText("Save Settings", math::vec2(500, 95), math::vec2(1, 1), ColorRGBA8());

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
	fog.init(math::vec4(600, 600, 32, 32), m_settings->isFogToggled);
	vignette.init(math::vec4(600, 525, 32, 32), m_settings->isVignetteToggled);
	debug.init(math::vec4(600, 450, 32, 32), m_settings->isDebugToggled);
	outline.init(math::vec4(600, 375, 32, 32), m_settings->renderOutline);
}

void PauseMenu::updateGUI(float deltaTime){
	save.update(m_inputManager, deltaTime);
	fog.update(m_inputManager, deltaTime);
	vignette.update(m_inputManager, deltaTime);
	debug.update(m_inputManager, deltaTime);
	outline.update(m_inputManager, deltaTime);
}

void PauseMenu::renderGUI(){
	save.render();
	fog.render();
	vignette.render();
	debug.render();
	outline.render();
}