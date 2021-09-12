#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iostream>
#include <cstdarg>
#include <chrono>
#include "Math.hpp"
#include "AABBox.hpp"
#include <GL/glew.h>

enum CollisionType {
	NONE, X_AXIS, Y_AXIS, Z_AXIS
};

namespace Utils {

	uint8_t* readFileToBuffer(const std::string& filePath);
	void freeBuffer(uint8_t* buffer);
	std::string readFileToString(const std::string& shaderName);
	bool isInside(const math::ivec2& mousePos, const math::vec4& destRect);
	bool isInRange(const math::vec3& a, const math::vec3& b, float range);
	CollisionType collideBoxes(AABB& a, const AABB& b);
	GLuint loadTexture(const std::string& _path);
	std::vector<std::string> tokenizeString(const std::string& _str);
	

}


