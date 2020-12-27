#pragma once
#include "GUIHandler.hpp"
#include "GameStates.hpp"
#include "Settings.hpp"
#include "Window.hpp"

#include <fstream>


class PauseMenu {
public:

     void init(GUIFont* font, Settings& settings);
     void update(GameStates& state, Settings& settings, uint8_t& blockID);
     void render();
     void destroy();

	void writeSettingsToDisk(Settings& settings);
	void loadSettingsFromDisk(Settings& settings);


private:

     GUIHandler m_handler;


};
