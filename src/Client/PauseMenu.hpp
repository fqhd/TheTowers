#pragma once

#include "GameStates.hpp"
#include "Player.hpp"
#include "Settings.hpp"
#include "Engine/GUI/GUIButton.hpp"
#include "Engine/GUI/GUICheckbox.hpp"
#include "Game.hpp"
#include <fstream>


class PauseMenu {
public:

	void init(InputManager* _manager, Settings* _settings, Game* _game, GUIRenderer* _guiRenderer);
	void update(GameStates& _state, float deltaTime);
	void render();

private:

	void handleInputs();

	// GUI
	GUIButton save;


	// Pointers
	GUIRenderer* m_guiRenderer = nullptr;
	InputManager* m_inputManager = nullptr;
	Settings* m_settings = nullptr;
	Game* m_game = nullptr;

};
