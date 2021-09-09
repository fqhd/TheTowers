#include "HUD.hpp"
#include "Item.hpp"

void HUD::init(Converter* _converter, Hotbar* _hotbar){
	m_converter = _converter;
	m_hotbar = _hotbar;
}

void HUD::render(){
	// Rendering crosshair
	GUIRenderer::drawRect(math::vec4(632, 352, 16, 16), math::vec4(0, 0, 1, 1), ColorRGBA8());

	// Rendering hotbar
	renderHotbar();
}

void HUD::renderHotbar(){
	// Rendering the hotbar
	GUIRenderer::drawRect(math::vec4(404, 2, 472, 52), math::vec4(0, 0, 1, 1), ColorRGBA8());

	// Rendering the items on the hotbar
	for(unsigned int i = 0; i < 11; i++) {
		Item item = m_hotbar->items[i];
		if(item.count > 0) {
			// Render the texture using the item renderer
			GUIRenderer::drawRect(math::vec4(414 + i * 32 + i * 10, 12, 32, 32), m_converter->itemIDToTextureUV(item.id), ColorRGBA8());
		}
	}

	// Rendering the selector
	GUIRenderer::drawRect(math::vec4(409 + m_hotbar->getSelectorLocation() * 42, 7, 42, 42), math::vec4(0, 0, 1, 1), ColorRGBA8());
}
