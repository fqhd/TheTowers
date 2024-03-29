#pragma once

#include "Game.hpp"
#include "PauseMenu.hpp"
#include "Settings.hpp"
#include "DebugMenu.hpp"
#include "GUIRenderer.hpp"
#include "BlockTextureHandler.hpp"
#include "Window.hpp"
#include "Clock.hpp"
#include "TextureArray.hpp"
#include "Converter.hpp"
#include "GUIUVLoader.hpp"
#include "FilePathManager.hpp"

class Program {
public:

	void run();

private:

	void initSystems();
	void gameloop();
	void cleanUp();
	
	NetworkManager m_networkManager;
	GameStates m_state = GameStates::PLAY;
	Settings m_settings;
	Clock m_deltaTimer;
	/*
	sf::IpAddress m_ip;
	*/
	
	Game m_game;
	PauseMenu m_pause;
	
};
