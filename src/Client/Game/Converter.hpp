#pragma once

#include "ItemID.hpp"
#include <glm/glm.hpp>
#include <unordered_map>


class Converter {
public:
	static uint8_t itemIDToBlockID(ItemID _id);
	static glm::vec4 itemIDToTextureUV(ItemID _id);
};
