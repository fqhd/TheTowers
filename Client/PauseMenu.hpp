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

     void init(GUIFont* font, Settings& settings);
     void update(GameStates& state, Settings& settings, Player& player);
     void updateValues(Settings& settings);
     void render();
     void destroy();

private:

     GUIHandler m_handler;


};

#endif
