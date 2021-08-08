#pragma once

#include <cstdint>
#include "Item.hpp"

struct Hotbar {
	uint8_t selectedItem = 0;
	Item items[9];
	uint8_t getSelectedBlockID(){
		return (uint8_t)items[selectedItem].id;
	}
};
