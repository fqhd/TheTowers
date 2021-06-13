#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "GameStates.hpp"
#include "Settings.hpp"
#include "Engine/Input/Window.hpp"
#include "Engine/GUI/GUIHandler.hpp"
#include "Player.hpp"
#include <fstream>


class PauseMenu {
public:

	void init(GUIFont* font);
	void update(GameStates& state, Player& player);
	void render();
	void destroy();

private:

	GUIHandler m_handler;

	void addImages();
	void addCheckboxes();
	void addText();
	void addButtons();


};

#endif
