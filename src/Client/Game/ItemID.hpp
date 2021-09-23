#pragma once

#include <cstdint>

// Items under the PICK **MUST** be blocks. This is because they are being mapped to block(sand, cobble, grass, etc...). We arenot using a hashmap for extra speed
// Items defined **AFTER** the pick are items that are not blocks(axe, bow, arrow, etc...)
enum class ItemID : uint8_t {
	GRASS,
	SNOW,
	DIRT,
	SAND,
	STONE,
	WOOD,
	LEAVES,
	CACTUS,
	COBBLE,
	DIAMOND,
	PICK
};
