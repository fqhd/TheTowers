#include "HUD.hpp"
#include "Item.hpp"

void HUD::init(GUIRenderer* _guiRenderer, Converter* _converter, ItemRenderer* _itemRenderer, Hotbar* _hotbar){
	m_guiRenderer = _guiRenderer;
	m_converter = _converter;
	m_itemRenderer = _itemRenderer;
	m_hotbar = _hotbar;
}

void HUD::render(){
	// Rendering crosshair
	m_guiRenderer->drawRect(math::vec4(632, 352, 16, 16), math::vec4(0, 0, 1, 1), m_guiRenderer->assets.getTexture("crosshair"), ColorRGBA8());

	// Rendering hotbar
	renderHotbar();
}

void HUD::renderHotbar(){
	m_guiRenderer->drawRect(math::vec4(404, 2, 472, 52), math::vec4(0, 0, 1, 1), m_guiRenderer->assets.getTexture("hotbar"), ColorRGBA8()); // Rendering the hotbar

	// Rendering the items on the hotbar
	m_itemRenderer->begin();
	for(unsigned int i = 0; i < 11; i++) {
		Item item = m_hotbar->items[i];
		if(item.count > 0) {
			// Render the texture using the item renderer
			m_itemRenderer->draw(math::vec2(414 + i * 32 + i * 10, 12), (unsigned int)m_converter->itemIDToTextureID(item.id));
		}
	}
	m_itemRenderer->end();
	m_itemRenderer->render();

	m_guiRenderer->drawRect(math::vec4(409 + m_hotbar->getSelectorLocation() * 42, 7, 42, 42), math::vec4(0, 0, 1, 1), m_guiRenderer->assets.getTexture("selector"), ColorRGBA8());
}
