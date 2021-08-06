#pragma once

#include "GUIRenderer.hpp"
#include "Config.hpp"
#include "Utils.hpp"

class HUD {
public:

	void render(GUIRenderer* _renderer);

private:

	void renderHotbar(GUIRenderer* _renderer);


};