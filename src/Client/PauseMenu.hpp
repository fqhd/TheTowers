#pragma once

#include "GameStates.hpp"
#include "Player.hpp"
#include "Settings.hpp"
#include "Engine/GUI/GUIRenderer.hpp"
#include "Engine/GUI/GUIAssets.hpp"
#include "Game.hpp"
#include <fstream>


class PauseMenu {
public:

	void init(InputManager* _manager, Settings* _settings, Game* _game, GUIRenderer* _guiRenderer, GUIAssets* _assets);
	void update(GameStates& _state, float deltaTime);
	void render();
	void destroy();

private:

	void initGUI();
	void handleInputs();


	GUIAssets* m_guiAssets = nullptr;
	GUIRenderer* m_guiRenderer = nullptr;
	InputManager* m_inputManager = nullptr;
	Settings* m_settings = nullptr;
	Game* m_game = nullptr;

	

};
