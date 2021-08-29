#include "Program.hpp"
#include <iostream>

const sf::IpAddress DEFAULT_IP = "tt.ilfez.club";

void Program::run(){
	m_ip = DEFAULT_IP;
	initSystems();
	startMenuLoop();
	initGame();
	gameloop();
	cleanUp();
}

void Program::initSystems(){
	m_converter.init();
	m_config.loadFromFile();
	m_settings.loadFromFile();
	m_window.create(m_config.getWindowWidth(), m_config.getWindowHeight(), "TheTowers", false, true);
	printf("hi\n");	
	m_inputManager.init(m_window.getWindowPtr(), m_config.getWindowHeight());
	printf("hi\n");	
	m_inputManager.setVerticalSync(true);
	printf("hi\n");	
	m_guiRenderer.init(m_config.getWindowWidth(), m_config.getWindowHeight());

	m_itemRenderer.init();
	m_textureArray.init("res/textures/sprite_sheet.png", 512);
}

void Program::initGame() {
	m_networkManager.connectToServer(DEFAULT_IP, &m_config);
	m_game.init(&m_inputManager, &m_networkManager, &m_guiRenderer, &m_textureArray, &m_config, &m_settings, &m_converter, &m_itemRenderer);
	m_pause.init(&m_inputManager, &m_settings, &m_guiRenderer);
}

void Program::startMenuLoop() {
	StartMenu *startMenu = new StartMenu;
	startMenu->init(&m_inputManager,
					&m_window,
					&m_guiRenderer,
					&m_config,
					&m_deltaTimer);
	startMenu->loop();
	m_ip = startMenu->getIp();
	delete startMenu;
}

void Program::gameloop(){
	m_deltaTimer.restart();
	while(m_state != GameStates::EXIT){
		m_window.clear();
		if(m_inputManager.processInput()) m_state = GameStates::EXIT;
		glViewport(0, 0, m_config.getWindowWidth(), m_config.getWindowHeight());

		float deltaTime = m_deltaTimer.getElapsedTime();
		m_deltaTimer.restart();

		m_guiRenderer.begin();
		if(m_state == GameStates::PLAY){
			m_game.update(m_state, deltaTime);
			m_game.render();
		}else if(m_state == GameStates::PAUSE){
			m_pause.update(m_state, deltaTime);
			m_game.render();
			m_pause.render();
		}
		m_guiRenderer.end();
		m_guiRenderer.render();

		m_window.update();
	}
}

void Program::cleanUp(){
	m_itemRenderer.destroy();
	m_textureArray.destroy();
	m_guiRenderer.destroy();
	m_game.destroy();
	m_window.close();
}
