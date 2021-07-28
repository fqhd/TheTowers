#include "Program.hpp"
#include <iostream>

void Program::run(sf::IpAddress& ip){
	initSystems(ip);
	gameloop();
	cleanUp();
}

void Program::initSystems(sf::IpAddress& _ip){
	m_config.loadFromFile();
	m_settings.loadFromFile();
	m_window.create(m_config.getWindowWidth(), m_config.getWindowHeight(), "TheTowers", false, false);
	m_inputManager.init(m_window.getWindowPtr(), m_config.getWindowHeight());
	m_textureHandler.init();
	m_guiRenderer.init(m_config.getWindowWidth(), m_config.getWindowHeight());
	m_networkManager.connectToServer(_ip, &m_config);
	m_game.init(&m_inputManager, &m_networkManager, &m_guiRenderer, &m_textureHandler, &m_config, &m_settings);
	m_pause.init(&m_inputManager, &m_settings, &m_config, &m_guiRenderer);
}

void Program::gameloop(){
	while(m_state != GameStates::EXIT){
		m_window.clear();
		if(m_inputManager.processInput()) m_state = GameStates::EXIT;
		glViewport(0, 0, m_config.getWindowWidth(), m_config.getWindowHeight());

		float deltaTime = m_clock.restart().asSeconds();

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
	m_textureHandler.destroy();
	m_guiRenderer.destroy();
	m_game.destroy();
	m_window.close();
}
