#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <epoxy/gl.h>
#include "Math.hpp"
#include <iostream>

class Window {
public:

	void create(unsigned int _width, unsigned int _height, const char* _title, bool _resizable = false, bool _decorated = true);
	void clear();
	void update();
	void close();
	GLFWwindow* getWindowPtr();



private:

	GLFWwindow* m_window = nullptr;

};
