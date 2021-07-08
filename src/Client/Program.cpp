#include "Program.hpp"
#include <iostream>

void Program::run(sf::IpAddress& ip){
	initSystems(ip);
	gameloop();
	cleanUp();
}

void Program::initSystems(sf::IpAddress& _ip){
	m_config.loadFromFile();
	m_window.create(1280, 720, "OpenCraft", false, true);
	m_inputManager.init(m_window.getWindowPtr());
	m_font.init("res/fonts/default.ttf", 32.0f, 512, 512);
	m_game.init(&m_inputManager, _ip, m_config);
	m_pause.init(&m_inputManager, &m_font);
}

void Program::gameloop(){
	while(m_state != GameStates::EXIT){
		m_window.clear();
		if(m_inputManager.processInput()) m_state = GameStates::EXIT;
		glViewport(0, 0, m_inputManager.getWindowSize().x, m_inputManager.getWindowSize().y);

		float deltaTime = m_clock.restart().asSeconds();

		if(m_state == GameStates::PLAY){
			m_game.update(m_state, m_player, deltaTime);
			m_game.render(m_player);
		}else if(m_state == GameStates::PAUSE){
			m_pause.update(m_state, deltaTime);
			m_game.render(m_player);
			m_pause.render();
		}

		m_window.update();
	}
}

void Program::cleanUp(){
	m_game.destroy();
	m_pause.destroy();
	m_window.close();
}
