#include "PauseMenu.hpp"
#include <iostream>

const float HLP = 600.0f; // Highest label position
const float SBL = 45.0f; // Space between labels

void PauseMenu::init(Settings* _settings){
	m_settings = _settings;
	initGUI();
}

void PauseMenu::initGUI(){
	saveButton.init(math::vec4(440, 80, 400, 50));

	float tmp = HLP;
	toggleVignette.init(math::vec4(320, tmp, 24, 24), m_settings->isVignetteToggled);
	toggleDebugView.init(math::vec4(365, tmp-=SBL, 24, 24), m_settings->isDebugToggled);
	toggleLegacyOutline.init(math::vec4(410, tmp-=SBL, 24, 24), m_settings->legacyOutline);
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

	// Labels

	float tmp = HLP;
	GUIRenderer::drawText("Vignette: ", math::vec2(175, tmp), math::vec2(0.75f), ColorRGBA8());
	GUIRenderer::drawText("Debug Mode: ", math::vec2(175, tmp-=SBL), math::vec2(0.75f), ColorRGBA8());
	GUIRenderer::drawText("Legacy Outline: ", math::vec2(175, tmp-=SBL), math::vec2(0.75f), ColorRGBA8());

	// Buttons
	GUIRenderer::drawText("Save Settings", math::vec2(500, 95), math::vec2(0.75f), ColorRGBA8());

	renderGUI();
}

void PauseMenu::syncSettingsWithGUI(){
	m_settings->isDebugToggled = toggleDebugView.isChecked();
	m_settings->isVignetteToggled = toggleVignette.isChecked();
	m_settings->legacyOutline = toggleLegacyOutline.isChecked();
	if(saveButton.isPressed()){
		m_settings->writeToFile();
	}
}

void PauseMenu::updateGUI(float deltaTime){
	saveButton.update(deltaTime);
	toggleVignette.update(deltaTime);
	toggleDebugView.update(deltaTime);
	toggleLegacyOutline.update(deltaTime);
}

void PauseMenu::renderGUI(){
	saveButton.render();
	toggleVignette.render();
	toggleDebugView.render();
	toggleLegacyOutline.render();
}
