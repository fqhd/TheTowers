#pragma once

#include "GameStates.hpp"
#include "Player.hpp"
#include "Settings.hpp"
#include "GUIButton.hpp"
#include "GUICheckbox.hpp"
#include "GUIInput.hpp"
#include "Game.hpp"
#include <fstream>


class PauseMenu {
public:

	void init(Settings* _settings);
	void update(GameStates& _state, float deltaTime);
	void render();

private:

	void syncSettingsWithGUI();
	void updateGUI(float deltaTime);
	void renderGUI();
	void initGUI();

	// GUI
	GUIButton save;
	GUICheckbox vignette;
	GUICheckbox debug;
	GUICheckbox outline;
	// Pointers
	Settings* m_settings = nullptr;

};
