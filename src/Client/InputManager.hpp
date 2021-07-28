#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <vector>
#include "Math.hpp"


class InputManager {
public:

	void init(GLFWwindow* _window, unsigned int _windowHeight);
	bool processInput();

	bool isKeyPressed(int _keyID);
	bool isKeyReleased(int _keyID);
	bool isKeyDown(int _keyID);
	bool wasKeyDown(int _keyID);
	char getLastKeyPressed() const; // A function which returns the last key pressed(-1 if no key was pressed and -2 if the backspace was pressed)
	bool hasFocus() const;

	void setMouseGrabbed(bool _grabbed);
	void setVerticalSync(bool _sync);
	float getDeltaMouseWheel();
	math::vec2 getMousePosition();
	math::vec2 getPreviousMousePosition();

private:

	std::unordered_map<int, bool> m_previousKeymap;
	math::vec2 m_previousMousePosition;

	GLFWwindow* m_window = nullptr;

};