#include "Utils.hpp"
#include "Image.hpp"

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

/*
	TODO: this tokenize function doesn't work properly it must be fixed.
	The goal of this function would be to take a string filled with both
	letters and spaces and return an array of strings corresponding to the
	letters/words separated by said spaces e.g:

	Input: "Hello, this is an example string"
	Output: "Hello", "this", "is", "an", "example", "string"

	The function shoudl also account for multiple spaces as exceptions. For example:

	Input: "   Hey, this     i    s me"
	Output: "Hey", "this", "i", "s", "me"
*/
std::vector<std::string> Utils::tokenizeString(const std::string& _str){
	std::vector<std::string> tokens;
	tokens.push_back(std::string());
	for(unsigned int i = 0; i < _str.size(); i++){
		if(_str[i] == ' '){
			tokens.push_back(std::string());
		}else{
			tokens.back().push_back(_str[i]);
		}
	}
	return tokens;
}

void Utils::freeBuffer(uint8_t* buffer){
	free(buffer);
}

GLuint Utils::loadTexture(const std::string& _path){
	Image image;
	image.loadFromFile(_path);

	GLuint tID;
	glGenTextures(1, &tID);
	glBindTexture(GL_TEXTURE_2D, tID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());

	glBindTexture(GL_TEXTURE_2D, 0);

	image.free();

	return tID;
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

bool Utils::isInside(const glm::ivec2& pos, const glm::vec4& destRect){
	return (pos.x >= destRect.x && pos.x <= destRect.x + destRect.z && pos.y >= destRect.y && pos.y <= destRect.y + destRect.w);
}

bool Utils::isInRange(const glm::vec3& a, const glm::vec3& b, float range){
	return glm::abs(glm::length(b - a)) < range;
}

CollisionType Utils::collideBoxes(AABB& a, const AABB& b){
	CollisionType collision = NONE; // Used to return the axis of the collision, set to NONE if there isn't any collision
	glm::vec3 aCenterPos = a.position + a.size / 2.0f;
	glm::vec3 bCenterPos = b.position + b.size / 2.0f;
	glm::vec3 delta = bCenterPos - aCenterPos;

	float intersectX = glm::abs(delta.x) - (b.size.x / 2 + a.size.x / 2);
	float intersectY = glm::abs(delta.y) - (b.size.y / 2 + a.size.y / 2);
	float intersectZ = glm::abs(delta.z) - (b.size.z / 2 + a.size.z / 2);

	if(intersectX < 0.0f && intersectY < 0.0f && intersectZ < 0.0f){ // Got a collision
		// The following if statements determine the axis with the greatest intersection(which will be the axis we push back on)
		if(intersectX > intersectY && intersectX > intersectZ){ // X axis is the greatest axis
			// This if statement checks on which side we should push back(positively or negatively)
			collision = X_AXIS;
			if(delta.x > 0.0f){
				a.position.x = b.position.x - a.size.x;
			}else{
				a.position.x = b.position.x + b.size.x;
			}
		}else if(intersectY > intersectZ){ // Y axis is the greatest axis
			// This if statement checks on which side we should push back(positively or negatively)
			collision = Y_AXIS;
			if(delta.y > 0.0f){
				a.position.y = b.position.y - a.size.y;
			}else{
				a.position.y = b.position.y + b.size.y;
			}
		}else{ // Z axis is the greatest axis
			// This if statement checks on which side we should push back(positively or negatively)
			collision = Z_AXIS;
			if(delta.z > 0.0f){
				a.position.z = b.position.z - a.size.z;
			}else{
				a.position.z = b.position.z + b.size.z;
			}
		}
	}
	return collision;
}
