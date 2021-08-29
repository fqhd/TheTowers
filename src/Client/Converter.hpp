#pragma once

#include "ItemID.hpp"

#include <unordered_map>

class Converter {
public:
	void init();
	uint8_t itemIDToBlockID(ItemID _id);
	unsigned int itemIDToTextureID(ItemID _id);

private:

	void populateTextureIndexMap();
	unsigned int itemTextures[256];

};
