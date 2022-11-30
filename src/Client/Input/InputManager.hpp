#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>


class InputManager {
public:

	static void init(GLFWwindow* _window);
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
	static glm::vec2 getMousePosition();
	static glm::vec2 getPreviousMousePosition();
	static glm::vec2 getWindowSize();
	static glm::vec2 getScaledMousePosition();

private:

	static std::unordered_map<int, bool> m_previousKeymap;
	static GLFWwindow* m_window;

};