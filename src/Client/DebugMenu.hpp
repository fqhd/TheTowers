#pragma once


#include "FrameCounter.hpp"
#include "Settings.hpp"
#include "GUIRenderer.hpp"
#include "Config.hpp"
#include "Utils.hpp"
#include "Player.hpp"

class DebugMenu {
public:

	void init(Config* _config);
	void render(const FrameCounter& _frameCounter, const Player& _player);

private:

	Config* m_config = nullptr;

};