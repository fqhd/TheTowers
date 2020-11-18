#pragma once
#include <string>
#include <fstream>
#include <algorithm>
#include <glm/glm.hpp>

enum LOG_TYPE{

    CONSOLE, DISK

};

namespace Utils{

     std::string loadShader(const char* shaderName);
     void log(const LOG_TYPE& type, const std::string& message);
     bool isInside(const glm::vec2& mousePos, const glm::vec4& destRect);
     bool isColliding(const glm::vec3& ourPos, const glm::vec3& blockPosition);

}
