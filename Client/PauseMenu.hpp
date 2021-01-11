#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H
#include "GUIHandler.hpp"
#include "GameStates.hpp"
#include "Settings.hpp"
#include "Window.hpp"
#include "Player.hpp"
#include <fstream>


class PauseMenu {
public:

     void init(Settings& settings);
     void update(GameStates& state, Settings& settings, Player& player);
     void updateValues(Settings& settings);
     void render();
     void destroy();

private:

	void addImages(Settings& settings);
	void addCheckboxes(Settings& settings);
	void addSliders(Settings& settings);
	void addKeyboxes(Settings& settings);

     GUIHandler m_handler;


};

#endif
