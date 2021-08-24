#pragma once

#include "Game.hpp"
#include "PauseMenu.hpp"
#include "Config.hpp"
#include "Settings.hpp"
#include "DebugMenu.hpp"
#include "GUIRenderer.hpp"
#include "BlockTextureHandler.hpp"
#include "Window.hpp"
#include "Timer.hpp"
#include "StartMenu.hpp"

class Program {
public:

	void run();


private:

	void initSystems();
	void initGame();
	void gameloop();
	void cleanUp();
	void createWindow();
	void startMenuLoop();

	BlockTextureHandler m_textureHandler;
	GUIRenderer m_guiRenderer;
	NetworkManager m_networkManager;
	Game m_game;
	PauseMenu m_pause;
	GameStates m_state = GameStates::PAUSE;
	InputManager m_inputManager;
	Config m_config;
	Settings m_settings;
	Window m_window;
	Timer m_deltaTimer;
	sf::IpAddress m_ip;

};
