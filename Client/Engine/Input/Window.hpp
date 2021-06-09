#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "../Libs/glad.h"
#include "../Utils/Utils.hpp"
#include "InputManager.hpp"


class Window {
public:

	static void create(unsigned int width, unsigned int height, const std::string& name, bool resizable, bool decorated);
	static void clear();
	static void update();
	static void close();

	//Window functions
	static void setVerticalSyncEnabled(bool enabled);
	static void setMouseCursorGrabbed(bool grabbed);
	static int getWidth();
	static int getHeight();
	static bool isResized();

	static bool isCloseRequested();

	static GLFWwindow* window;


private:

	static void windowResized(GLFWwindow* window, int width, int height);

	static int m_width;
	static int m_height;

	static bool m_isResized;
	static bool m_closeRequested;

};

#endif
