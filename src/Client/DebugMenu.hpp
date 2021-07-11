#pragma once

#include "Engine/GUI/GUICanvas.hpp"
#include "Game.hpp"
#include "Settings.hpp"

class DebugMenu {
public:

	void init(Game* _game, GUICanvas* _canvas);
	void render();


private:

	void updateGUI();
	void initGUI();

	GUICanvas* m_canvas = nullptr;
	Game* m_game = nullptr;


};