#pragma once

#include "ItemID.hpp"

#include <unordered_map>

class Converter {
public:
	void init();
	
	uint8_t itemIDToBlockID(ItemID _id);
	uint8_t itemIDToTextureID(ItemID _id);

private:

	void populateTextureIndexMap();
	uint8_t itemTextures[256];

};
