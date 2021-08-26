#pragma once

#include "ItemID.hpp"
#include "TextureIndex.hpp"

#include <unordered_map>

class Converter {
public:
	void init();
	uint8_t itemIDToBlockID(ItemID _id);
	TextureIndex itemIDToTextureID(ItemID _id);

private:
	void populateTextureIndexMap();
	std::unordered_map<ItemID, TextureIndex> m_textureIndexMap;
};
