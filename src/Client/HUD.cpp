#include "HUD.hpp"

void HUD::render(GUIRenderer* _renderer){
	_renderer->drawRect(math::vec4(632, 352, 16, 16), math::vec4(0, 0, 1, 1), _renderer->assets.getCrosshairTexture(), ColorRGBA8()); // Rendering the crosshair
	renderHotbar(_renderer); // Rendering Hotbar
}

void HUD::renderHotbar(GUIRenderer* _renderer){
	_renderer->drawRect(math::vec4(404, 2, 472, 52), math::vec4(0, 0, 1, 1), _renderer->assets.getHotbarTexture(), ColorRGBA8()); // Rendering the hotbar
}
