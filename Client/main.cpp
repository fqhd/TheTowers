#include <SFML/Network.hpp>
#include "Game.hpp"
#include "Constants.hpp"
#include "Window.hpp"
#include "GameStates.hpp"
#include "PauseMenu.hpp"
#include "GUIFont.hpp"
#include <iostream>





bool getIP(sf::IpAddress& ip);

int main() {

	srand(time(0));

	sf::IpAddress ip;
	if(!getIP(ip)){
		return 0;
	}


	//Program Variables
	Player player;
	Game game;
	PauseMenu pause;
	GUIFont font;
	GameStates state;
	Settings settings;
	sf::Clock clock;

	//Initializing objects
	Constants::loadFromFile();
	Constants::printDebugMessage();
	settings.readFromFile();
	Window::create(Constants::getScreenWidth(), Constants::getScreenHeight(), "Game", false, true);
	Window::setMouseCursorGrabbed(true);
	InputManager::init(Window::window);
	font.init("res/fonts/thinfont-thin.ttf");
	game.init(&font, ip);
	pause.init(&font, settings);
	state = GameStates::PLAY;

	clock.restart();
	while(state != GameStates::EXIT){

		while(state == GameStates::PLAY){
			Window::clear();

			float deltaTime = clock.restart().asSeconds();

			game.update(settings, deltaTime, state, player);
			game.render(settings, player, deltaTime);

			Window::update();
			if(Window::isCloseRequested()) state = GameStates::EXIT;
		}

		while(state == GameStates::PAUSE){
			Window::clear();

			pause.update(state, settings, player);
			game.render(settings, player, clock.getElapsedTime().asSeconds());
			pause.render();

			clock.restart();
			Window::update();
			if(Window::isCloseRequested()) state = GameStates::EXIT;

		}

	}

	settings.writeToFile();

	game.destroy();
	pause.destroy();

	Window::close();


	return 0;
}

bool getIP(sf::IpAddress& ip){

	std::string s;
	std::cout << "Enter server IP: ";
	std::cin >> s;
	ip = s;
	if(s.empty()){
		return false;
	}
	return true;
}
