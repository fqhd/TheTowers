#pragma once

enum GameMode : uint8_t {
	SURVIVAL,
	CREATIVE,
	SPECTATOR
};

inline bool GameModeCanFly(GameMode gmode) {
	return ((gmode == GameMode::CREATIVE) || (gmode == GameMode::SPECTATOR));
}