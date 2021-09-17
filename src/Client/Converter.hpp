#pragma once

#include "ItemID.hpp"
#include "Vec4.hpp"
#include <unordered_map>


class Converter {
public:
	static uint8_t itemIDToBlockID(ItemID _id);
	static math::vec4 itemIDToTextureUV(ItemID _id);
};
