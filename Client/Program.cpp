#include "Program.hpp"

void Program::run(sf::IpAddress& ip){

	initSystems(ip);
	gameloop();
	cleanUp();

}

void Program::initSystems(sf::IpAddress& ip){

	// Initializing program stuff


	// Initializing game stuff
	Constants::loadFromFile();
	Constants::printDebugMessage();
	Window::create(Constants::getScreenWidth(), Constants::getScreenHeight(), "BuildBattle", true, true);
	Window::setMouseCursorGrabbed(true);
	InputManager::init(Window::window);
	m_font.init("res/fonts/default.ttf", 32.0f, 512, 512);
	m_game.init(ip);
	m_pause.init(&m_font);

}

void Program::gameloop(){

	while(m_state != GameStates::EXIT){
		Window::clear();
		if(InputManager::processInput(Window::window)) m_state = GameStates::EXIT;
		glViewport(0, 0, Window::getWidth(), Window::getHeight());

		if(m_state == GameStates::PLAY){
			m_game.update(m_clock.restart().asSeconds(), m_state, m_player);
			m_game.render(m_player);
		}else if(m_state == GameStates::PAUSE){
			m_pause.update(m_state, m_player);
			m_pause.render();
		}

		Window::update();
	}

}

void Program::cleanUp(){
	m_game.destroy();
	m_pause.destroy();
	Window::close();
}