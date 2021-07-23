#include "DebugMenu.hpp"

void DebugMenu::init(Game* _game, const Config& _config){
	m_game = _game;
	m_config = _config;

	m_fps_text = "FPS: ";
}

void DebugMenu::render(GUIRenderer* _renderer){
	math::vec2 debugMenuPos(10, m_config.getWindowHeight()-20);
	// update 
	if (m_game->frameCounter.get_current_frame() == FRAMES_SIZE-1) {
		m_fps_text = "FPS: " + std::to_string((int)m_game->frameCounter.get_average());
	}

	_renderer->drawText(m_fps_text, 
	                    math::vec2(debugMenuPos.x, debugMenuPos.y), 
						math::vec2(0.3f, 0.3f), 
						ColorRGBA8());
}