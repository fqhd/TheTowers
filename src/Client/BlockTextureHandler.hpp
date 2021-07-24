#pragma once

#include "TextureArray.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

struct BlockTexture {
	BlockTexture(){}
	BlockTexture(uint16_t _t){
		top = _t;
		side = _t;
		bot = _t;
	}
	BlockTexture(uint16_t _top, uint16_t _side, uint16_t _bot){
		top = _top;
		side = _side;
		bot = _bot;
	}
	uint16_t top = 0;
	uint16_t side = 0;
	uint16_t bot = 0;
};

class BlockTextureHandler {
public:

	void init();
	void bind();
	void unbind();
	void destroy();
	BlockTexture getTextureFromBlockID(uint8_t _blockID);

private:

	// Private functions
	void loadBlockTexturesFromFile();

	// Private variables
	TextureArray m_texturePack;
	BlockTexture m_blockTextures[255];

};