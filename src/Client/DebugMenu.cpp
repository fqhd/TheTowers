#include "DebugMenu.hpp"

void DebugMenu::init(Config* _config){
	m_config = _config;
}

void DebugMenu::render(GUIRenderer* _renderer, const FrameCounter& _frameCounter, const Player& _player){
	// Drawing FPS
	_renderer->drawText("FPS: " + std::to_string(_frameCounter.getAverage()), math::vec2(10, 700), math::vec2(0.5f, 0.5f), ColorRGBA8());

	// Drawing player coordinates
	math::vec3 coords = _player.getEyePos();
	_renderer->drawText("X: " + std::to_string(coords.x), math::vec2(10, 675), math::vec2(0.5, 0.5), ColorRGBA8());
	_renderer->drawText("Y: " + std::to_string(coords.y), math::vec2(10, 650), math::vec2(0.5, 0.5), ColorRGBA8());
	_renderer->drawText("Z: " + std::to_string(coords.z), math::vec2(10, 625), math::vec2(0.5, 0.5), ColorRGBA8());
}