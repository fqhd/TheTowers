#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "GameStates.hpp"
#include "Engine/GUI/GUIHandler.hpp"
#include "Player.hpp"
#include "Settings.hpp"
#include "Game.hpp"
#include <fstream>


class PauseMenu {
public:

	void init(InputManager* _manager, GUIFont* _font, Settings* _settings, TextureArray* _textureArray, Game* _game);
	void update(GameStates& _state, float deltaTime);
	void render();
	void destroy();

private:

	void initGUI();
	void handleInputs();

	GUIHandler m_handler;
	InputManager* m_inputManager = nullptr;
	Settings* m_settings = nullptr;
	Game* m_game = nullptr;

};

#endif
