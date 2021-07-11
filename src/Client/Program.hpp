#pragma once

#include "Player.hpp"
#include "Game.hpp"
#include "PauseMenu.hpp"
#include "Engine/Input/Window.hpp"
#include "Config.hpp"
#include "Settings.hpp"
#include "Engine/GUI/GUIHandler.hpp"


class Program {
public:

	void run(sf::IpAddress& ip);


private:

	void initSystems(sf::IpAddress& ip);
	void gameloop();
	void cleanUp();
	void initInputManager();

	GUIHandler m_guiHandler;
	TextureArray m_texturePack;
	Player m_player;
	GUIFont m_font;
	Game m_game;
	PauseMenu m_pause;
	GameStates m_state = GameStates::PAUSE;
	InputManager m_inputManager;
	Window m_window;
	Config m_config;
	Settings m_settings;
	sf::Clock m_clock;

};
