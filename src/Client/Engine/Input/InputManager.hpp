#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <glm/glm.hpp>
#include <vector>


class InputManager {
public:

	void init(GLFWwindow* _window);
	bool processInput();

	bool isKeyPressed(int _keyID);
	bool isKeyReleased(int _keyID);
	bool isKeyDown(int _keyID);
	bool wasKeyDown(int _keyID);

	void setMouseGrabbed(bool _grabbed);
	void setVerticalSync(bool _sync);
	float getDeltaMouseWheel();
	glm::vec2 getWindowSize();
	glm::vec2 getMousePosition();
	glm::vec2 getScaledMousePosition();
	glm::vec2 getPreviousMousePosition();

private:

	std::unordered_map<int, bool> m_previousKeymap;
	glm::vec2 m_previousMousePosition;

	GLFWwindow* m_window;

};

