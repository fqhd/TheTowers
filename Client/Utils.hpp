#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <cstdint>


namespace Utils{

     std::string readFileToString(const std::string& shaderName);
     bool isInside(const glm::vec2& mousePos, const glm::vec4& destRect);
     bool isInRange(const glm::vec3& a, const glm::vec3& b, float range);
     void log(const std::string& message);
     glm::vec2 flipCoords(const glm::vec2& coords, float height);
     glm::vec2 mapPoint(const glm::vec2& point, const glm::vec2& pointDimensions, const glm::vec2& desiredDimensions);


}

#endif
