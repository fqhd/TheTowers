#include "Program.hpp"

const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;

void Program::run(sf::IpAddress& ip){

	initSystems(ip);
	gameloop();
	cleanUp();

}

void Program::initSystems(sf::IpAddress& ip){
	initWindow();
	initGL();
	m_inputManager.init(&m_window);
	m_font.init("res/fonts/default.ttf", 32.0f, 512, 512);
	m_game.init(ip);
	m_pause.init(&m_font);
}

void Program::initWindow(){
	sf::ContextSettings cSettings;
	cSettings.majorVersion = 3;
	cSettings.minorVersion = 3;
	cSettings.depthBits = 24;
	cSettings.antialiasingLevel = 4;
	m_window.create(sf::VideoMode(1280.0f, 720.0f), "BuildBattle", sf::Style::Default, cSettings);
	m_window.setVerticalSyncEnabled(true);
	m_window.setMouseCursorGrabbed(true);
}

void Program::initGL(){
	
}

void Program::gameloop(){

	while(m_state != GameStates::EXIT){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(m_inputManager.processInput()) m_state = GameStates::EXIT;

		glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);

		if(m_state == GameStates::PLAY){
			m_game.update(m_clock.restart().asSeconds(), m_state, m_player);
			m_game.render(m_player);
		}else if(m_state == GameStates::PAUSE){
			m_pause.update(m_state, m_player);
			m_pause.render();
		}

		m_window.display();
	}

}

void Program::cleanUp(){
	m_game.destroy();
	m_pause.destroy();
	Window::close();
}