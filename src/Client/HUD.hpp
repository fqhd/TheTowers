#pragma once

#include "Engine/GUI/GUIRenderer.hpp"

class HUD {
public:

	void render(GUIRenderer* _renderer);

private:

	void renderHotbar(GUIRenderer* _renderer);


};