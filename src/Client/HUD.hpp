#pragma once

#include "GUIRenderer.hpp"
#include "Config.hpp"
#include "Utils.hpp"
#include "Hotbar.hpp"
#include "Converter.hpp"


class HUD {
public:

	void init(Converter* _converter, Hotbar* _hotbar);
	void render();

private:

	void renderHotbar();

	Hotbar* m_hotbar = nullptr;
	Converter* m_converter = nullptr;

};
