#include "PauseMenu.hpp"
#include <iostream>

void PauseMenu::init(Settings* _settings){
	m_settings = _settings;
	initGUI();
}

void PauseMenu::update(GameStates& _state, float deltaTime){
	// Change state back to game if the user presses on escape
	if(InputManager::isKeyPressed(GLFW_KEY_ESCAPE)){
		InputManager::setMouseGrabbed(true);
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
	GUIRenderer::drawText("Vignette: ", math::vec2(175, 600), math::vec2(1, 1), ColorRGBA8());
	GUIRenderer::drawText("Debug Mode: ", math::vec2(175, 525), math::vec2(1, 1), ColorRGBA8());
	GUIRenderer::drawText("Block Outline: ", math::vec2(175, 450), math::vec2(1, 1), ColorRGBA8());
	GUIRenderer::drawText("Save Settings", math::vec2(500, 95), math::vec2(1, 1), ColorRGBA8());

	renderGUI();
}

void PauseMenu::syncSettingsWithGUI(){
	m_settings->isDebugToggled = debug.isChecked();
	m_settings->isVignetteToggled = vignette.isChecked();
	m_settings->renderOutline = outline.isChecked();
	if(save.isPressed()){
		m_settings->writeToFile();
	}
}

void PauseMenu::initGUI(){
	save.init(math::vec4(440, 80, 400, 50));
	vignette.init(math::vec4(600, 600, 32, 32), m_settings->isVignetteToggled);
	debug.init(math::vec4(600, 525, 32, 32), m_settings->isDebugToggled);
	outline.init(math::vec4(600, 450, 32, 32), m_settings->renderOutline);
}

void PauseMenu::updateGUI(float deltaTime){
	save.update(deltaTime);
	vignette.update(deltaTime);
	debug.update(deltaTime);
	outline.update(deltaTime);
}

void PauseMenu::renderGUI(){
	save.render();
	vignette.render();
	debug.render();
	outline.render();
}