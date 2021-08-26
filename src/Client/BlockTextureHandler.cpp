#include "BlockTextureHandler.hpp"

void tokenizeString(const std::string& _str, std::vector<std::string>& _tokens){
	_tokens.clear();
	_tokens.push_back(std::string());
	for(unsigned int i = 0; i < _str.size(); i++){
		if(_str[i] == ' '){
			_tokens.push_back(std::string());
		}else{
			_tokens.back().push_back(_str[i]);
		}
	}
}

void BlockTextureHandler::loadBlockTexturesFromFile(){
	std::ifstream is;
	is.open("TextureArrangement");
	if(is.fail()){
		std::cout << "Failed to open texture arrangment file, it should be under res/textures/texture_arrangement.txt" << std::endl;
		return;
	}

	std::string line;
	std::vector<std::string> tokens;
	unsigned int index = 0;
	while(std::getline(is, line)){
		tokenizeString(line, tokens);
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


