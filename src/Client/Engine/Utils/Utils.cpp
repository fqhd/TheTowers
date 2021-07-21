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

void Utils::collideBoxes(AABB& a, const AABB& b){
	math::vec3 aCenterPos = a.position + a.size / 2;
	math::vec3 bCenterPos = b.position + b.size / 2;
	math::vec3 delta = bCenterPos - aCenterPos;

	float intersectX = math::fabs(delta.x) - (b.size.x / 2 + a.size.x / 2);
	float intersectY = math::fabs(delta.y) - (b.size.y / 2 + a.size.y / 2);
	float intersectZ = math::fabs(delta.z) - (b.size.z / 2 + a.size.z / 2);

	if(intersectX < 0.0f && intersectY < 0.0f && intersectZ < 0.0f){ // Got a collision
		// The following if statements determine the axis with the greatest intersection(which will be the axis we push back on)
		if(intersectX > intersectY && intersectX > intersectZ){ // X axis is the greatest axis
			// This if statement checks on which side we should push back(positively or negatively)
			if(delta.x > 0.0f){
				a.position.x = b.position.x - a.size.x;
			}else{
				a.position.x = b.position.x + b.size.x;
			}
		}else if(intersectY > intersectZ){ // Y axis is the greatest axis
			// This if statement checks on which side we should push back(positively or negatively)
			if(delta.y > 0.0f){
				a.position.y = b.position.y - a.size.y;
			}else{
				a.position.y = b.position.y + b.size.y;
			}
		}else{ // Z axis is the greatest axis
			// This if statement checks on which side we should push back(positively or negatively)
			if(delta.z > 0.0f){
				a.position.z = b.position.z - a.size.z;
			}else{
				a.position.z = b.position.z + b.size.z;
			}
		}
	}
}

math::vec2 Utils::mapPoint(const math::vec2& d, const math::vec2& o, const math::vec2& t){
	return math::vec2((d.x/o.x) * t.x, (d.y/o.y) * t.y);
}

math::vec4 Utils::mapDestRect(const math::vec4& d, const math::vec2& o, const math::vec2& t){
	return math::vec4((d.x/o.x) * t.x, (d.y/o.y) * t.y, (d.z/o.x) * t.x, (d.w/o.y) * t.y);
}
