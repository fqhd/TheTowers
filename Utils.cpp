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

void Utils::log(const LOG_TYPE& type, const std::string& message){

    switch(type){
        case CONSOLE:
            printf("%s\n", message.c_str());
        break;
        case DISK:
            std::ofstream os;
            os.open("res/logs.txt");
            os << message;
            os.close();
            //If message happens here print error message to log.txt
        break;
    }

}

bool Utils::isColliding(const glm::vec3& a, const glm::vec3& b){
	if(a.x + PLAYER_WIDTH >= b.x && a.x <= b.x + 1 &&
	a.y + PLAYER_HEIGHT >= b.y && a.y <= b.y + 1 &&
	a.z + PLAYER_WIDTH >= b.z && a.z <= b.z + 1){
		return true;
	}
	return false;
}
