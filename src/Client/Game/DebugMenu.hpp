#pragma once


#include "FrameCounter.hpp"
#include "Settings.hpp"
#include "GUIRenderer.hpp"
#include "Utils.hpp"
#include "Player.hpp"

class DebugMenu {
public:

	void render(const FrameCounter& _frameCounter, const Player& _player);

};