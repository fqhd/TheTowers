#pragma once

#include <unordered_map>
#include <string>
#include <glm/glm.hpp>

namespace GUIUVLoader {

	void init();
	glm::vec4 getUV(const std::string& uv);

};
