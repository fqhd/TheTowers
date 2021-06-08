#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H
#include "GUICanvas.hpp"
#include "GameStates.hpp"
#include "Settings.hpp"
#include "Window.hpp"
#include "Player.hpp"
#include <fstream>


class PauseMenu {
public:

	void init(Settings& settings, GUICanvas& workspace);
	void update(GameStates& state, Settings& settings, Player& player, GUICanvas& workspace);

private:

	void applySettingsToWorkspace(Settings& settings, GUICanvas& workspace);
	void applyWorkspaceToSettings(GUICanvas& workspace, Settings& settings);
	void updateValues(Settings& settings, GUICanvas& workspace);
	void addImages(Settings& settings, GUICanvas& workspace);
	void addCheckboxes(Settings& settings, GUICanvas& workspace);
	void addSliders(Settings& settings, GUICanvas& workspace);
	void addKeyboxes(Settings& settings, GUICanvas& workspace);
	void addText(Settings& settings, GUICanvas& workspace);
	void updatePlayerBlock(Player& player, GUICanvas& workspace);


};

#endif
