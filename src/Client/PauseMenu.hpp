#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "GameStates.hpp"
#include "Engine/GUI/GUIHandler.hpp"
#include "Player.hpp"
#include <fstream>


class PauseMenu {
public:

	void init(InputManager* _manager, GUIFont* _font);
	void update(GameStates& _state);
	void render();
	void destroy();

private:

	GUIHandler m_handler;
	InputManager* m_inputManager;

};

#endif
