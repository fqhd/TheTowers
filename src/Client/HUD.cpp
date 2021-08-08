#include "HUD.hpp"

void HUD::render(GUIRenderer* _renderer, Hotbar& _hotbar){
	_renderer->drawRect(math::vec4(632, 352, 16, 16), math::vec4(0, 0, 1, 1), _renderer->assets.getCrosshairTexture(), ColorRGBA8()); // Rendering the crosshair
	renderHotbar(_renderer, _hotbar); // Rendering Hotbar
}

void HUD::renderHotbar(GUIRenderer* _renderer, Hotbar& _hotbar){
	_renderer->drawRect(math::vec4(404, 2, 472, 52), math::vec4(0, 0, 1, 1), _renderer->assets.getHotbarTexture(), ColorRGBA8()); // Rendering the hotbar
	for(unsigned int i = 0; i < 11; i++) {
		_renderer->drawRect(math::vec4(i * 32, 0, 32, 32), math::vec4());
	}
}
