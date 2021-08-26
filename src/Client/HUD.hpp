#pragma once

#include "GUIRenderer.hpp"
#include "Config.hpp"
#include "Utils.hpp"
#include "Hotbar.hpp"
#include "ItemRenderer.hpp"
#include "Converter.hpp"


class HUD {
public:

	void init(GUIRenderer* _guiRenderer, Converter* _converter, ItemRenderer* _itemRenderer, Hotbar* _hotbar);
	void render();

private:

	void renderHotbar();

	ItemRenderer* m_itemRenderer = nullptr;
	GUIRenderer* m_guiRenderer = nullptr;
	Hotbar* m_hotbar = nullptr;
	Converter* m_converter = nullptr;

};
