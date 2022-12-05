#include "Program.hpp"
#include <iostream>

void Program::run(){
	initSystems();
	gameloop();
	cleanUp();
}

void Program::initSystems(){
	FilePathManager::init();
	m_settings.loadFromFile();
	Window::create(WINDOW_WIDTH, WINDOW_HEIGHT, "TheTowers");
	InputManager::init(Window::getWindowPtr());
	InputManager::setVerticalSync(true);
	InputManager::setMouseGrabbed(true);
	GUIRenderer::init(WINDOW_WIDTH, WINDOW_HEIGHT, GUIAssets::getTexture("gui_sprite_sheet"));
	GUIUVLoader::init();
	m_networkManager.connectToServer();
	m_game.init(&m_networkManager, &m_settings, &m_state);
	m_pause.init(&m_settings);
}

void Program::gameloop(){
	m_deltaTimer.restart();
	while(m_state != GameStates::EXIT){
		Window::clear();
		if(InputManager::processInput()) m_state = GameStates::EXIT;
		float deltaTime = m_deltaTimer.getElapsedTime();
		m_deltaTimer.restart();
		m_game.updateEssentials(deltaTime);

		if(m_state == GameStates::PLAY){
			m_game.update(deltaTime);
			m_game.render();
		}else if(m_state == GameStates::PAUSE){
			m_pause.update(m_state, deltaTime);
			m_game.render();
			m_pause.render();
		}
		GUIRenderer::batch();
		GUIRenderer::render();

		Window::update();
	}
}

void Program::cleanUp(){
	m_networkManager.Disconnect();
	GUIAssets::destroy();
	GUIRenderer::destroy();
	m_game.destroy();
	Window::close();
}
