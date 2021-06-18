#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <glm/glm.hpp>


class InputManager {
public:

	void init(GLFWwindow* _window);
	bool processInput();

	bool isKeyPressed(unsigned int keyID);
	bool isKeyReleased(unsigned int keyID);

	void setMouseGrabbed(bool _grabbed);
	void setVerticalSync(bool _sync);
	float getDeltaMouseWheel();
	glm::vec2 getWindowSize();
	glm::vec2 getMousePosition();
	glm::vec2 getScaledMousePosition();
	glm::vec2 getPreviousMousePosition();

private:

	void updateMousePos();

	glm::vec2 m_previousMousePosition;
	glm::vec2 m_mousePosition;
	GLFWwindow* m_window;

};

#endif
