#pragma once
#include "GUIHandler.hpp"
#include "GameStates.hpp"
#include "Settings.hpp"
#include <fstream>

class PauseMenu {
public:

     void init(GUIFont* font, Settings& settings);
     void update(sf::Window& window, InputManager& manager, GameStates& state, Settings& settings);
     void render();
     void destroy();

	void writeSettingsToDisk(Settings& settings);
	void loadSettingsFromDisk(Settings& settings);


private:

     GUIHandler m_handler;



};
