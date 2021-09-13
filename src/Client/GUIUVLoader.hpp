#pragma once

#include <unordered_map>
#include <string>
#include "Vec4.hpp"

namespace GUIUVLoader {

	void init();
	math::vec4 getUV(const std::string& uv);

};
