#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

struct BlockTexture {
	BlockTexture(){}
	BlockTexture(uint8_t _t){
		top = _t;
		side = _t;
		bot = _t;
	}
	BlockTexture(uint8_t _top, uint8_t _side, uint8_t _bot){
		top = _top;
		side = _side;
		bot = _bot;
	}
	uint8_t top = 0;
	uint8_t side = 0;
	uint8_t bot = 0;
};

class BlockTextureHandler {
public:

	void loadBlockTexturesFromFile();
	BlockTexture getTextureFromBlockID(uint8_t _blockID);

private:

	// Private variables
	BlockTexture m_blockTextures[255];

};
