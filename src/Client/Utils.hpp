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

namespace Utils {

	uint8_t* readFileToBuffer(const std::string& filePath);
	void freeBuffer(uint8_t* buffer);
	std::string readFileToString(const std::string& shaderName);
	bool isInside(const math::ivec2& mousePos, const math::vec4& destRect);
	bool isInRange(const math::vec3& a, const math::vec3& b, float range);
	CollisionType collideBoxes(AABB& a, const AABB& b);
	math::vec2 mapPoint(const math::vec2& d, float ox, float oy, float tx, float ty); // Maps a point from original windowSize to target windowSize
	math::vec4 mapDestRect(const math::vec4& destRect, float ox, float oy, float tx, float ty); // Maps a dest rect from original windowSize to target windowSize

}

 