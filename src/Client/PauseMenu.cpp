#include "PauseMenu.hpp"
#include <iostream>

void PauseMenu::init(InputManager* _manager, Settings* _settings, Config* _config, GUIRenderer* _guiRenderer){
	m_config = _config;
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
	unsigned int ww = m_config->getWindowWidth();
	unsigned int wh = m_config->getWindowHeight();

	// Background, 1920, 1080, ww, wh)
	m_guiRenderer->drawRect(Utils::mapDestRect(math::vec4(258, 138, 1404, 804), 1920, 1080, ww, wh), math::vec4(0, 0, 1, 1), m_guiRenderer->assets.getGrassTexture(), ColorRGBA8());
	m_guiRenderer->drawRect(Utils::mapDestRect(math::vec4(260, 140, 1400, 800), 1920, 1080, ww, wh), math::vec4(0, 0, 10, 7), m_guiRenderer->assets.getGrassTexture(), ColorRGBA8(34, 40, 50, 255));

	// Text
	m_guiRenderer->drawText("Fog: ", Utils::mapPoint(math::vec2(325, 850), 1920, 1080, ww, wh), math::vec2(1, 1), ColorRGBA8());
	m_guiRenderer->drawText("Vignette: ", Utils::mapPoint(math::vec2(325, 750), 1920, 1080, ww, wh), math::vec2(1, 1), ColorRGBA8());
	m_guiRenderer->drawText("Debug Mode: ", Utils::mapPoint(math::vec2(325, 650), 1920, 1080, ww, wh), math::vec2(1, 1), ColorRGBA8());
	m_guiRenderer->drawText("Block Outline: ", Utils::mapPoint(math::vec2(325, 550), 1920, 1080, ww, wh), math::vec2(1, 1), ColorRGBA8());

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
	unsigned int ww = m_config->getWindowWidth();
	unsigned int wh = m_config->getWindowHeight();
	
	save.init(Utils::mapDestRect(math::vec4(760, 175, 400, 50), 1920, 1080, ww, wh));
	fog.init(Utils::mapDestRect(math::vec4(800, 850, 48, 48), 1920, 1080, ww, wh), m_settings->isFogToggled);
	vignette.init(Utils::mapDestRect(math::vec4(800, 750, 48, 48), 1920, 1080, ww, wh), m_settings->isVignetteToggled);
	debug.init(Utils::mapDestRect(math::vec4(800, 650, 48, 48), 1920, 1080, ww, wh), m_settings->isDebugToggled);
	outline.init(Utils::mapDestRect(math::vec4(800, 550, 48, 48), 1920, 1080, ww, wh), m_settings->renderOutline);
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