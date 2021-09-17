#include "HUD.hpp"
#include "Item.hpp"

void HUD::init(Hotbar* _hotbar){
	m_hotbar = _hotbar;
}

void HUD::render(){
	// Rendering crosshair
	GUIRenderer::drawRect(math::vec4(632, 352, 16, 16), GUIUVLoader::getUV("Crosshair"), ColorRGBA8());

	// Rendering hotbar
	renderHotbar();
}

void HUD::renderHotbar(){
	// Rendering the hotbar
	GUIRenderer::drawRect(math::vec4(404, 2, 472, 52), GUIUVLoader::getUV("Hotbar"), ColorRGBA8());

	// Rendering the items on the hotbar
	for(unsigned int i = 0; i < 11; i++) {
		Item item = m_hotbar->items[i];
		if(item.count > 0) {
			// Render the texture using the item renderer
			GUIRenderer::drawRect(math::vec4(414 + i * 32 + i * 10, 12, 32, 32), Converter::itemIDToTextureUV(item.id), ColorRGBA8());
		}
	}

	// Rendering the selector
	GUIRenderer::drawRect(math::vec4(409 + m_hotbar->getSelectorLocation() * 42, 7, 42, 42), GUIUVLoader::getUV("Selector"), ColorRGBA8());
}
