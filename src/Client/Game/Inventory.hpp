#pragma once

#include "InputManager.hpp"
#include "GUIRenderer.hpp"
#include "Hotbar.hpp"

class Inventory {
public:

	void update(InputManager& _im);
	void render(GUIRenderer& _guiRenderer, Hotbar& hotbar);

	Item mouseItem;

};