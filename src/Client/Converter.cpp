#include "Converter.hpp"

void Converter::init(){
	populateTextureIndexMap();
}

uint8_t Converter::itemIDToBlockID(ItemID _id) {
	uint8_t blockID = (uint8_t)_id;
	if(blockID < (uint8_t)ItemID::PICK){
		return blockID;
	}
	return 0;
}

TextureIndex Converter::itemIDToTextureID(ItemID _blockID) {
	auto it = m_textureIndexMap.find(_blockID);
	if(it != m_textureIndexMap.end()){
		return it->second;
	}
	return TextureIndex::CACTUS_SIDE;
}

void Converter::populateTextureIndexMap(){
	m_textureIndexMap[ItemID::GRASS] = TextureIndex::GRASS_SIDE;
	m_textureIndexMap[ItemID::SNOW] = TextureIndex::SNOW_SIDE;
	m_textureIndexMap[ItemID::DIRT] = TextureIndex::DIRT;
	m_textureIndexMap[ItemID::SAND] = TextureIndex::SAND;
	m_textureIndexMap[ItemID::STONE] = TextureIndex::STONE;
	m_textureIndexMap[ItemID::WOOD] = TextureIndex::WOOD_SIDE;
	m_textureIndexMap[ItemID::LEAVES] = TextureIndex::LEAVES;
	m_textureIndexMap[ItemID::CACTUS] = TextureIndex::CACTUS_SIDE;
	m_textureIndexMap[ItemID::COBBLE] = TextureIndex::COBBLE;
	m_textureIndexMap[ItemID::DIAMOND] = TextureIndex::DIAMOND;
}
