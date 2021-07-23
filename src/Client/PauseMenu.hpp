#pragma once

#include "GameStates.hpp"
#include "Player.hpp"
#include "Settings.hpp"
#include "Engine/GUI/GUIButton.hpp"
#include "Engine/GUI/GUICheckbox.hpp"
#include "Engine/GUI/GUIInput.hpp"
#include "Game.hpp"
#include <fstream>


class PauseMenu {
public:

	void init(InputManager* _manager, Settings* _settings, Config* _config, GUIRenderer* _guiRenderer);
	void update(GameStates& _state, float deltaTime);
	void render();

private:

	void syncSettingsWithGUI();
	void updateGUI(float deltaTime);
	void renderGUI();
	void initGUI();

	// GUI
	GUIButton save;
	GUICheckbox fog;
	GUICheckbox vignette;
	GUICheckbox debug;
	GUICheckbox outline;
	GUIInput input;
	// Pointers
	GUIRenderer* m_guiRenderer = nullptr;
	InputManager* m_inputManager = nullptr;
	Settings* m_settings = nullptr;
	Config* m_config = nullptr;

};
