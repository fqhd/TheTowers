#pragma once

#include <cstdint>

// Items must be defined in the same order as their are retreived from ItemTexture.cpp
enum class ItemID : uint8_t {
	NONE,
	Grass,
	Snow,
	Dirt,
	Sand,
	Stone,
	Wood,
	Leaves,
	Cactus,
	Cobble,
	Diamond
};
