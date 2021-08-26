#pragma once

#include "Game.hpp"
#include "PauseMenu.hpp"
#include "Config.hpp"
#include "ItemRenderer.hpp"
#include "Settings.hpp"
#include "DebugMenu.hpp"
#include "GUIRenderer.hpp"
#include "BlockTextureHandler.hpp"
#include "Window.hpp"
#include "Timer.hpp"
#include "StartMenu.hpp"
#include "TextureArray.hpp"
#include "Converter.hpp"

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

	ItemRenderer m_itemRenderer;
	Converter m_converter;
	TextureArray m_textureArray;
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


};
