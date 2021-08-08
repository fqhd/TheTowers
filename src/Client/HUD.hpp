#pragma once

#include "GUIRenderer.hpp"
#include "Config.hpp"
#include "Utils.hpp"
#include "Hotbar.hpp"

class HUD {
public:

	void render(GUIRenderer* _renderer, Hotbar& _hotbar);

private:

	void renderHotbar(GUIRenderer* _renderer, Hotbar& _hotbar);


};