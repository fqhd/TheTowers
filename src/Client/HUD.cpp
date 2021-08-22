#include "HUD.hpp"
#include "Item.hpp"

void HUD::render(GUIRenderer* _renderer, Hotbar& _hotbar){
	_renderer->drawRect(math::vec4(632, 352, 16, 16), math::vec4(0, 0, 1, 1), _renderer->assets.getTexture("crosshair"), ColorRGBA8()); // Rendering the crosshair
	renderHotbar(_renderer, _hotbar); // Rendering Hotbar
}

void HUD::renderHotbar(GUIRenderer* _renderer, Hotbar& _hotbar){
	_renderer->drawRect(math::vec4(404, 2, 472, 52), math::vec4(0, 0, 1, 1), _renderer->assets.getTexture("hotbar"), ColorRGBA8()); // Rendering the hotbar
	for(unsigned int i = 0; i < 11; i++) {
		ItemID itemID = _hotbar.items[i].id;
		if(itemID != ItemID::NONE){
			_renderer->drawRect(math::vec4(414 + i * 32 + i * 10, 12, 32, 32), _renderer->assets.getItemTexture().getUVQuadFromItemID(itemID), _renderer->assets.getItemTexture().getTextureID(), ColorRGBA8());
		}
	}
	_renderer->drawRect(math::vec4(409 + _hotbar.getSelectorLocation() * 42, 7, 42, 42), math::vec4(0, 0, 1, 1), _renderer->assets.getTexture("selector"), ColorRGBA8());
}
