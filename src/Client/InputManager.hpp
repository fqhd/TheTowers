#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <vector>
#include "Math.hpp"


class InputManager {
public:

	static void init(GLFWwindow* _window, unsigned int _windowHeight);
	static bool processInput();

	static bool isKeyPressed(int _keyID);
	static bool isKeyReleased(int _keyID);
	static bool isKeyDown(int _keyID);
	static bool wasKeyDown(int _keyID);
	static char getLastKeyPressed(); // A function which returns the last key pressed(-1 if no key was pressed and -2 if the backspace was pressed)
	static bool hasFocus();

	static void setMouseGrabbed(bool _grabbed);
	static void setVerticalSync(bool _sync);
	static float getDeltaMouseWheel();
	static math::vec2 getMousePosition();
	static math::vec2 getPreviousMousePosition();

private:

	static std::unordered_map<int, bool> m_previousKeymap;
	static math::vec2 m_previousMousePosition;
	static GLFWwindow* m_window;

};