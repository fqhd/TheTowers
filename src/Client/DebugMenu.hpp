#pragma once


#include "FrameCounter.hpp"
#include "Settings.hpp"
#include "GUIRenderer.hpp"
#include "Game.hpp"
class DebugMenu {
public:

	void init(Game* _game, const Config& _config);
	void render(GUIRenderer* _renderer);

private:

	Game* m_game = nullptr;
	Config m_config;
	std::string m_fps_text;

};