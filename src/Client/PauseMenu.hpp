#pragma once

#include "GameStates.hpp"
#include "Player.hpp"
#include "Settings.hpp"
#include "Engine/GUI/GUIRenderer.hpp"
#include "Game.hpp"
#include <fstream>


class PauseMenu {
public:

	void init(InputManager* _manager, Settings* _settings, Game* _game, GUIRenderer* _guiRenderer);
	void update(GameStates& _state, float deltaTime);
	void render();
	void destroy();

private:

	void initGUI();
	void handleInputs();


	GUIRenderer* m_guiRenderer = nullptr;
	InputManager* m_inputManager = nullptr;
	Settings* m_settings = nullptr;
	Game* m_game = nullptr;

	

};
