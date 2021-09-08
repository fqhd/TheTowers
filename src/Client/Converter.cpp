#include "Converter.hpp"
#include <fstream>
#include <iostream>

const unsigned int ITEM_WIDTH = 8;
const unsigned int IMAGE_WIDTH = 256;
const unsigned int IMAGE_WIDTH_IN_ITEMS = IMAGE_WIDTH / ITEM_WIDTH;

// Items that are under
uint8_t Converter::itemIDToBlockID(ItemID _id) {
	uint8_t blockID = (uint8_t)_id;
	if(blockID < (uint8_t)ItemID::PICK){
		return blockID + 1;
	}
	return 0;
}

math::vec4 Converter::itemIDToTextureUV(ItemID _id) {
	float x = (uint8_t)_id % IMAGE_WIDTH_IN_ITEMS;
	float y = (uint8_t)_id / IMAGE_WIDTH_IN_ITEMS;

	return math::vec4(x * ITEM_WIDTH / (float)IMAGE_WIDTH,
					y * ITEM_WIDTH / (float)IMAGE_WIDTH,
					ITEM_WIDTH / (float)IMAGE_WIDTH,
					ITEM_WIDTH / (float)IMAGE_WIDTH);
}

