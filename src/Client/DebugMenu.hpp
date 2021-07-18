#pragma once

#include "Game.hpp"
#include "Settings.hpp"
#include "Engine/GUI/GUIRenderer.hpp"

class DebugMenu {
public:

	void init(Game* _game);
	void render(GUIRenderer* _renderer);

private:

	Game* m_game = nullptr;


};