#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iostream>
#include <cstdarg>
#include <chrono>
#include "../Math/Math.hpp"


namespace Utils {

	uint8_t* readFileToBuffer(const std::string& filePath);
	void freeBuffer(uint8_t* buffer);
	std::string readFileToString(const std::string& shaderName);
	bool isInside(const math::ivec2& mousePos, const math::vec4& destRect);
	bool isInRange(const math::vec3& a, const math::vec3& b, float range);
	// math::vec2 mapPoint(const math::vec2& point, const math::vec2& pointDimensions, const math::vec2& desiredDimensions);


}

 
