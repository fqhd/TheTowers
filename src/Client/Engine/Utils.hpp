#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iostream>
#include <cstdarg>
#include <chrono>
#include "AABBox.hpp"
#include <GLAD/glad.h>
#include <glm/glm.hpp>

enum CollisionType {
	NONE, X_AXIS, Y_AXIS, Z_AXIS
};

namespace Utils {

	uint8_t* readFileToBuffer(const std::string& filePath);
	void freeBuffer(uint8_t* buffer);
	std::string readFileToString(const std::string& shaderName);
	bool isInside(const glm::ivec2& mousePos, const glm::vec4& destRect);
	bool isInRange(const glm::vec3& a, const glm::vec3& b, float range);
	CollisionType collideBoxes(AABB& a, const AABB& b);
	GLuint loadTexture(const std::string& _path);
	std::vector<std::string> tokenizeString(const std::string& _str);
	

}


