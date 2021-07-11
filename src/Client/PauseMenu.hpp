#pragma once

#include "GameStates.hpp"
#include "Engine/GUI/GUIHandler.hpp"
#include "Player.hpp"
#include "Settings.hpp"
#include "Game.hpp"
#include <fstream>


class PauseMenu {
public:

	void init(InputManager* _manager, Settings* _settings, GUICanvas* _canvas, Game* _game);
	void update(GameStates& _state, float deltaTime);
	void render();
	void destroy();

private:

	void initGUI();
	void handleInputs();

	GUICanvas* m_canvas = nullptr;
	InputManager* m_inputManager = nullptr;
	Settings* m_settings = nullptr;
	Game* m_game = nullptr;

};
