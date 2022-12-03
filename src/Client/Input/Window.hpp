#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GLAD/glad.h>
#include <glm/glm.hpp>
#include <iostream>

namespace Window {
	void create(unsigned int _width, unsigned int _height, const char* _title);
	void clear();
	void update();
	void close();
	GLFWwindow* getWindowPtr();
}
