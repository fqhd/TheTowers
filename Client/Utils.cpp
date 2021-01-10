#include "Utils.hpp"

void Utils::printDividor(const std::string& name){
	printf("%s\n", ("--------------------------- " + name + " ---------------------------").c_str());
}

std::string Utils::readFileToString(const std::string& shaderName) {
	std::string shaderCode = "";
	std::string line;
	std::ifstream is;
	is.open(shaderName);
	if(is.fail()){
		log("Failed to find file: " + shaderName);
		is.close();
		return shaderCode;
	}

	while(std::getline(is, line)) {
		shaderCode += line + "\n";
	}

	is.close();
	return shaderCode;
}

bool Utils::isInside(const glm::vec2& pos, const glm::vec4& destRect){
    return (pos.x >= destRect.x && pos.x <= destRect.x + destRect.z && pos.y >= destRect.y && pos.y <= destRect.y + destRect.w);
}

bool Utils::isInRange(const glm::vec3& a, const glm::vec3& b, float range){
	return std::fabs(glm::length(b - a)) < range;
}

void Utils::log(const std::string& message){
	printf("%s\n", message.c_str());
}

glm::vec2 Utils::flipCoords(const glm::vec2& coords, float height){
	return glm::vec2(coords.x, height - coords.y);
}

glm::vec2 Utils::mapPoint(const glm::vec2& point, const glm::vec2& pointDimensions, const glm::vec2& desiredDimensions){
	glm::vec2 mappedPoint;
	float xPercent = point.x / pointDimensions.x;
	float yPercent = point.y / pointDimensions.y;
	mappedPoint.x = xPercent * desiredDimensions.x;
	mappedPoint.y = yPercent * desiredDimensions.y;
	return mappedPoint;
}
