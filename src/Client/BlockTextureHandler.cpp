#include "BlockTextureHandler.hpp"
#include "Utils.hpp"

void BlockTextureHandler::loadBlockTexturesFromFile(){
	std::ifstream is;
	is.open("TextureArrangement");
	if(is.fail()){
		std::cout << "Failed to open texture arrangment file, it should be under res/textures/texture_arrangement.txt" << std::endl;
		return;
	}

	std::string line;
	unsigned int index = 0;
	while(std::getline(is, line)){
		std::vector<std::string> tokens = Utils::tokenizeString(line);
		uint16_t top = std::stoi(tokens.at(0));
		uint16_t side = std::stoi(tokens.at(1));
		uint16_t bot = std::stoi(tokens.at(2));
		m_blockTextures[index] = BlockTexture(top, side, bot);
		index++;
	}

	is.close();
}

BlockTexture BlockTextureHandler::getTextureFromBlockID(uint8_t _blockID) {
	return m_blockTextures[_blockID - 1];
}


