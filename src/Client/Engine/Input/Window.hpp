#ifndef WINDOW_H
#define WINDOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>

class Window {
public:

	void create(unsigned int _width, unsigned int _height, const char* _title, bool _resizable = false, bool _decorated = true);
	void clear();
	void update();
	void close();

	

private:

	GLFWwindow* m_window = nullptr;

};

#endif