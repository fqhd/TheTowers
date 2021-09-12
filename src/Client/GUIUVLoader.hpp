#pragma once

#include <unordered_map>
#include <string>
#include "Vec4.hpp"

class GUIUVLoader {
public:

	void init();
	math::vec4 getUV(const std::string& uv);

private:

	std::unordered_map<std::string, math::vec4> m_uvMap;

};