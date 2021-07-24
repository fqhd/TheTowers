#pragma once

#include "Game.hpp"
#include "PauseMenu.hpp"
#include "Config.hpp"
#include "Settings.hpp"
#include "DebugMenu.hpp"
#include "GUIRenderer.hpp"
#include "BlockTextureHandler.hpp"
#include <SFML/OpenGL.hpp>


class Program {
public:

	void run(sf::IpAddress& ip);


private:

	void initSystems(sf::IpAddress& ip);
	void gameloop();
	void cleanUp();
	void createWindow();

	BlockTextureHandler m_textureHandler;
	GUIRenderer m_guiRenderer;
	NetworkManager m_networkManager;

	Game m_game;
	PauseMenu m_pause;
	GameStates m_state = GameStates::PLAY;
	InputManager m_inputManager;
	Config m_config;
	Settings m_settings;
	DebugMenu m_debugMenu;

	sf::Window m_window;
	sf::Clock m_clock;

};
