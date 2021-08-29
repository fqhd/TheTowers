#include "Converter.hpp"
#include <fstream>
#include <iostream>

void Converter::init(){
	populateTextureIndexMap();
}

// Items that are under
uint8_t Converter::itemIDToBlockID(ItemID _id) {
	uint8_t blockID = (uint8_t)_id;
	if(blockID < (uint8_t)ItemID::PICK){
		return blockID;
	}
	return 0;
}

unsigned int Converter::itemIDToTextureID(ItemID _id) {
	return itemTextures[(uint8_t)_id];
}

void Converter::populateTextureIndexMap(){
	std::ifstream is;
	is.open("ItemTextureArrangement");
	if(is.fail()){
		std::cout << "Failed to load ItemTextureArrangement" << std::endl;
		return;
	}
	unsigned int index = 0;
	unsigned int posInArray = 0;
	while(is >> index){
		itemTextures[posInArray] = index;
		posInArray++;
	}
	is.close();
}
