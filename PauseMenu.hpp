#pragma once
#include "GUIHandler.hpp"
#include "GameStates.hpp"

class PauseMenu {
public:

     void init(GUIFont* font);
     void update(sf::Window& window, InputManager& manager, GameStates& state);
     void render();
     void destroy();


private:

     GUIHandler m_handler;



};
