#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include "Math.hpp"
#include <iostream>

class Window {
public:

	static void create(unsigned int _width, unsigned int _height, const char* _title, bool _resizable = false, bool _decorated = true);
	static void clear();
	static void update();
	static void close();
	static GLFWwindow* getWindowPtr();

private:

	static GLFWwindow* m_window;

};
