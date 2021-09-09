#include "Program.hpp"
#include <iostream>

const sf::IpAddress DEFAULT_IP = "tt.ilfez.club";

void Program::run(){
	m_ip = DEFAULT_IP;
	initSystems();
	gameloop();
	cleanUp();
}

void Program::initSystems(){
	m_config.loadFromFile();
	m_settings.loadFromFile();
	m_window.create(m_config.getWindowWidth(), m_config.getWindowHeight(), "TheTowers", false, true);
	m_inputManager.init(m_window.getWindowPtr(), m_config.getWindowHeight());
	m_inputManager.setVerticalSync(true);
	GUIRenderer::init(m_config.getWindowWidth(), m_config.getWindowHeight(), GUIAssets::getTexture("gui_sprite_sheet"));
	m_blockTextureHandler.loadBlockTexturesFromFile();
	m_textureArray.init("res/textures/sprite_sheet.png", 512);
	m_networkManager.connectToServer(DEFAULT_IP, &m_config);
	m_game.init(&m_inputManager, &m_networkManager, &m_textureArray, &m_config, &m_settings, &m_converter, &m_blockTextureHandler);
	m_pause.init(&m_inputManager, &m_settings);
}

void Program::gameloop(){
	m_deltaTimer.restart();
	while(m_state != GameStates::EXIT){
		m_window.clear();
		if(m_inputManager.processInput()) m_state = GameStates::EXIT;
		glViewport(0, 0, m_config.getWindowWidth(), m_config.getWindowHeight());

		float deltaTime = m_deltaTimer.getElapsedTime();
		m_deltaTimer.restart();

		if(m_state == GameStates::PLAY){
			m_game.update(m_state, deltaTime);
			m_game.render();
		}else if(m_state == GameStates::PAUSE){
			m_pause.update(m_state, deltaTime);
			m_game.render();
			m_pause.render();
		}
		GUIRenderer::batch();
		GUIRenderer::render();

		m_window.update();
	}
}

void Program::cleanUp(){
	m_textureArray.destroy();
	GUIRenderer::destroy();
	m_game.destroy();
	m_window.close();
}
