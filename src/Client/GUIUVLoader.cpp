#include "GUIUVLoader.hpp"
#include <fstream>
#include <iostream>
#include "Utils.hpp"

const float TEXTURE_SIZE = 256.0f;

void GUIUVLoader::init(){
	std::ifstream is;
	is.open("GUIUVArrangement");
	if(is.fail()){
		std::cout << "GUIUVLoader: Failed to open GUIUVArragnement" << std::endl;
		return;
	}
	std::string line;
	while(std::getline(is, line)){
		std::vector<std::string> tokens = Utils::tokenizeString(line);
		std::string key = tokens.at(0);
		math::vec4 uvRect;
		uvRect.x = std::stoi(tokens.at(1)) / TEXTURE_SIZE;
		uvRect.y = std::stoi(tokens.at(2)) / TEXTURE_SIZE;
		uvRect.z = std::stoi(tokens.at(3)) / TEXTURE_SIZE;
		uvRect.w = std::stoi(tokens.at(4)) / TEXTURE_SIZE;
		m_uvMap[key] = uvRect;
	}
	is.close();
}

math::vec4 GUIUVLoader::getUV(const std::string& name){
	auto it = m_uvMap.find(name);
	if(it != m_uvMap.end()){
		return it->second;
	}
	std::cout << "GUIUVLoader: Failed to find " + name + " in UVMap data structure" << std::endl;
	return math::vec4(0, 0, 1, 1);
}