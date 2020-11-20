#include "Game.hpp"
#include "Window.hpp"
#include "Button.hpp"
#include "InputBox.hpp"
#include "GameStates.hpp"
#include "PauseMenu.hpp"
#include "GUIFont.hpp"
#include <SFML/Network.hpp>

bool getIP(sf::IpAddress& ip);
void game();

int main(){

	srand(time(0));

	/*
	sf::IpAddress ip;
	if(!getIP(ip)){
		return 0;
	}
	*/

	//Primitive Variables
	float deltaTime;
	uint8_t blockID = 0;

	//SFML Variables
	sf::Clock clock;

	//Program Variables
	Game game;
	Window window;
	PauseMenu pause;
	InputManager manager;
	GUIFont font;
	GameStates state;
	Settings settings;


	//Initializing objects
	window.init();
	clock.restart();
	font.init("res/fonts/thinfont-thin.ttf");
	game.init(&font);
	pause.init(window.window, &font, settings);
	state = GameStates::PLAY;

	while(state != GameStates::EXIT){
		window.clear();
		manager.processInput(window.window);

		switch(state) {
			case GameStates::PLAY:

			deltaTime = clock.restart().asSeconds();

			game.update(window.window, manager, deltaTime, state, blockID);
			game.render(settings, deltaTime);

			break;
			case GameStates::PAUSE:

			pause.update(window.window, manager, state, settings, blockID);
			game.render(settings, deltaTime);
			pause.render();

			break;
		}



		if(manager.isCloseRequested()){
			state = GameStates::EXIT;
		}
		window.update();

	}

	window.close();






	return 0;
}

bool getIP(sf::IpAddress& ip){

	sf::RenderWindow window;
	sf::Font font;
	InputManager manager;
	Button button;
	InputBox box;

	window.create(sf::VideoMode(800, 600), "Get IP", sf::Style::Titlebar);
	sf::VideoMode deskTop = sf::VideoMode::getDesktopMode();
	window.setPosition(sf::Vector2i((deskTop.getDesktopMode().width / 2) - window.getSize().x/2, (deskTop.getDesktopMode().height / 2) - window.getSize().y/2));
	window.setVerticalSyncEnabled(true);

	font.loadFromFile("res/fonts/arial.ttf");
	button.init(sf::FloatRect(300, 400, 200, 30), "Button", &font);
	box.init(sf::FloatRect(250.0f, 300.0f, 300.0f, 30.0f), &font);


	while(window.isOpen()){
		window.clear();
		manager.processInput(window);

		button.update(manager, window);
		button.render(window);

		box.update(manager, window);
		box.render(window);

		window.display();

		if(manager.isCloseRequested()){
			window.close();
		}
		if(button.isPressed()){
			ip = box.getString();
			window.close();
			return true;
		}
	}

	return false;
}
