#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "Engine/GUI/GUICanvas.hpp"
#include "GameStates.hpp"
#include "Settings.hpp"
#include "Engine/Input/Window.hpp"
#include "Engine/GUI/GUIHandler.hpp"
#include "Player.hpp"
#include <fstream>


class PauseMenu {
public:

	void init(Settings& settings, GUICanvas& workspace);
	void update(GameStates& state, Settings& settings, Player& player, GUICanvas& workspace);

private:

	GUIHandler m_handler;

	void addImages();
	void addCheckboxes();
	void addText();
	void addButtons();
	void updatePlayerBlock(Player& player, GUICanvas& workspace);


};

#endif
