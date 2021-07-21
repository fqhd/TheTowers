#pragma once

#include "Engine/GUI/GUIRenderer.hpp"
#include "Config.hpp"
#include "Engine/Utils/Utils.hpp"

class HUD {
public:

	void render(GUIRenderer* _renderer, Config* _config);

private:

	void renderHotbar(GUIRenderer* _renderer, Config* _config);


};