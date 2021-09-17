#pragma once

#include "GUIRenderer.hpp"
#include "Config.hpp"
#include "Utils.hpp"
#include "Hotbar.hpp"
#include "Converter.hpp"
#include "GUIUVLoader.hpp"


class HUD {
public:

	void init(Hotbar* _hotbar);
	void render();

private:

	void renderHotbar();

	Hotbar* m_hotbar = nullptr;

};
