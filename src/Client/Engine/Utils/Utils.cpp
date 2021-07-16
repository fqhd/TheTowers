#include "Utils.hpp"


uint8_t* Utils::readFileToBuffer(const std::string& filePath) {

	std::ifstream file(filePath, std::ios::binary);
	if (file.fail()) {
		perror(filePath.c_str());
		return nullptr;
	}

	file.seekg(0, std::ios::end);

	unsigned int fileSize = (unsigned int)file.tellg();
	file.seekg(0, std::ios::beg);

	fileSize -= (unsigned int)file.tellg();

	//Creating new buffer
	uint8_t* buffer = (uint8_t*)malloc(fileSize);

	//Reading data into buffer
	file.read((char*)buffer, fileSize);
	file.close();

	return buffer;
}

void Utils::freeBuffer(uint8_t* buffer){
	free(buffer);
}

std::string Utils::readFileToString(const std::string& shaderName) {
	std::string shaderCode = "";
	std::string line;
	std::ifstream is;
	is.open(shaderName);
	if(is.fail()){
		std::cout << "Failed to find file: " << shaderName << std::endl;
		is.close();
		return shaderCode;
	}

	while(std::getline(is, line)) {
		shaderCode += line + "\n";
	}

	is.close();
	return shaderCode;
}

bool Utils::isInside(const math::ivec2& pos, const math::vec4& destRect){
	return (pos.x >= destRect.x && pos.x <= destRect.x + destRect.z && pos.y >= destRect.y && pos.y <= destRect.y + destRect.w);
}

bool Utils::isInRange(const math::vec3& a, const math::vec3& b, float range){
	return math::fabs(math::length(b - a)) < range;
}

/*
math::vec2 Utils::mapPoint(const math::vec2& point, const math::vec2& pointDimensions, const math::vec2& desiredDimensions){
	math::vec2 mappedPoint;
	float xPercent = point.x / pointDimensions.x;
	float yPercent = point.y / pointDimensions.y;
	mappedPoint.x = xPercent * desiredDimensions.x;
	mappedPoint.y = yPercent * desiredDimensions.y;
	return mappedPoint;
}
*/