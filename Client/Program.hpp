#ifndef PROGRAM_H
#define PROGRAM_H

#include "Player.hpp"
#include "Game.hpp"
#include "PauseMenu.hpp"


class Program {
public:

	void run(sf::IpAddress& ip);


private:

	void initSystems();
	void gameloop();
	void cleanUp();

	Player player;
	Game game;
	PauseMenu pause;
	GameStates state = GameStates::PLAY;
	sf::Clock clock;

};

#endif