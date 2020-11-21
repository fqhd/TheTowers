#include "Utils.hpp"
#include "Constants.hpp"

std::string Utils::loadShader(const char* shaderName){
	std::string shaderCode = "";
	std::string line;
	std::ifstream is;
	is.open(shaderName);

	while(std::getline(is, line)){
		shaderCode += line + "\n";
	}

	is.close();
	return shaderCode;
}

bool Utils::isInside(const glm::vec2& mousePos, const glm::vec4& destRect){
    return (mousePos.x >= destRect.x && mousePos.x <= destRect.x + destRect.z && mousePos.y >= destRect.y && mousePos.y <= destRect.y + destRect.w);
}
