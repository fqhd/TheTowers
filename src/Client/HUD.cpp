#include "HUD.hpp"

void HUD::render(GUIRenderer* _renderer){
	_renderer->drawRect(math::vec4(952, 532, 16, 16), math::vec4(0, 0, 1, 1), _renderer->assets.getCrosshairTexture(), 0.0f, ColorRGBA8()); // Rendering the crosshair
	renderHotbar(_renderer);
}

void HUD::renderHotbar(GUIRenderer* _renderer){
	_renderer->drawRect(math::vec4(724, 4, 472, 52), math::vec4(0, 0, 1, 1), _renderer->assets.getHotbarTexture(), 0.0f, ColorRGBA8()); // Rendering the crosshair
	
}
