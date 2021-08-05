#include "HUD.hpp"

const float HOTBAR_WIDTH = 472 * 2;
const float HOTBAR_HEIGHT = 52 * 2;

void HUD::render(GUIRenderer* _renderer, Config* _config){
	unsigned int ww = _config->getWindowWidth();
	unsigned int wh = _config->getWindowHeight();
	
	_renderer->drawRect(Utils::mapDestRect(math::vec4(952, 532, 16, 16), 1920, 1080, ww, wh), math::vec4(0, 0, 1, 1), _renderer->assets.getCrosshairTexture(), ColorRGBA8()); // Rendering the crosshair
	renderHotbar(_renderer, _config);
}

void HUD::renderHotbar(GUIRenderer* _renderer, Config* _config){
	unsigned int ww = _config->getWindowWidth();
	unsigned int wh = _config->getWindowHeight();

	_renderer->drawRect(Utils::mapDestRect(math::vec4(1920 / 2 - HOTBAR_WIDTH / 2, 4, HOTBAR_WIDTH, HOTBAR_HEIGHT), 1920, 1080, ww, wh), math::vec4(0, 0, 1, 1), _renderer->assets.getHotbarTexture(), ColorRGBA8()); // Rendering the hotbar
}
