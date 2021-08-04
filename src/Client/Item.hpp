#pragma once

#include "ItemID.hpp"

struct Item {
	ItemID id = ItemID::NONE;
	uint8_t amount = 0;
};