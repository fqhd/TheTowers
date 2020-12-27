#include <SFML/Network.hpp>
#include <iostream>

#include "Game.hpp"
#include "Window.hpp"
#include "GameStates.hpp"
#include "PauseMenu.hpp"
#include "GUIFont.hpp"

bool getIP(sf::IpAddress& ip);

int main() {

	srand(time(0));

	sf::IpAddress ip;
	if(!getIP(ip)){
		return 0;
	}

	//Primitive Variables
	float deltaTime;
	uint8_t blockID = 215;

	//SFML Variables
	sf::Clock clock;

	//Program Variables
	Game game;
	PauseMenu pause;
	GUIFont font;
	GameStates state;
	Settings settings;


	//Initializing objects
	Window::create(1280, 720, "Game", false, true);
	Window::setMouseCursorGrabbed(true);
	InputManager::init(Window::window);
	clock.restart();
	font.init("res/fonts/thinfont-thin.ttf");
	game.init(&font, ip);
	pause.init(&font, settings);
	state = GameStates::PLAY;

	while(state != GameStates::EXIT){
		Window::clear();
		InputManager::processInput(Window::window);

		switch(state) {
			case GameStates::PLAY:

			deltaTime = clock.restart().asSeconds();

			game.update(settings, deltaTime, state, blockID);
			game.render(settings, deltaTime);

			break;
			case GameStates::PAUSE:

			pause.update(state, settings, blockID);
			game.render(settings, deltaTime);
			pause.render();

			break;
		}



		if(Window::isCloseRequested()){
			state = GameStates::EXIT;
		}
		Window::update();

	}

	Window::close();


	return 0;
}

bool getIP(sf::IpAddress& ip){

	std::string s;
	std::cin >> s;
	ip = s;
	if(s.empty()){
		return false;
	}
	return true;
}
