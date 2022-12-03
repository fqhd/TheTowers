#include "DebugMenu.hpp"

void DebugMenu::render(const FrameCounter& _frameCounter, const Player& _player){
	// Drawing FPS
	GUIRenderer::drawText("FPS: " + std::to_string(_frameCounter.getFrameRate()), glm::vec2(10, 700), glm::vec2(0.5f, 0.5f), ColorRGBA8());

	// Drawing player coordinates
	glm::vec3 coords = _player.getEyePos();
	GUIRenderer::drawText("X: " + std::to_string(coords.x), glm::vec2(10, 675), glm::vec2(0.5, 0.5), ColorRGBA8());
	GUIRenderer::drawText("Y: " + std::to_string(coords.y), glm::vec2(10, 650), glm::vec2(0.5, 0.5), ColorRGBA8());
	GUIRenderer::drawText("Z: " + std::to_string(coords.z), glm::vec2(10, 625), glm::vec2(0.5, 0.5), ColorRGBA8());
}
