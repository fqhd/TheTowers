#include "InputManager.hpp"
#include "../Utils/Utils.hpp"
#include <iostream>


glm::vec2 mousePosition;
std::unordered_map<int, bool> keymap;

void keyPressed(int _keyID){
	keymap[_keyID] = true;
}

void keyReleased(int _keyID){
	keymap[_keyID] = false;
}

void keyPressed(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods){
	if(_action == GLFW_PRESS){
		keyPressed(_key);
	}else if(_action == GLFW_RELEASE){
		keyReleased(_key);
	}
}

void buttonPressed(GLFWwindow* _window, int _button, int _action, int _mods){
	if(_action == GLFW_PRESS){
		keyPressed(_button);
	}else if(_action == GLFW_RELEASE){
		keyReleased(_button);
	}
}

void mouseMoved(GLFWwindow* window, double _xpos, double _ypos){
	mousePosition = glm::vec2((float)_xpos, (float)_ypos);
}

void InputManager::init(GLFWwindow* _window) {
	m_window = _window;
	glfwSetKeyCallback(_window, keyPressed);
	glfwSetMouseButtonCallback(_window, buttonPressed);
	glfwSetCursorPosCallback(_window, mouseMoved);

	// We must inialize the mouse position function on init because the mouseMoved() callback function only sets the mouse position when the mouse position is moved.
	double x, y;
	glfwGetCursorPos(_window, &x, &y);
	mousePosition = glm::vec2(x, y);

	
}

bool InputManager::processInput() {
	m_previousMousePosition = mousePosition;
	m_previousKeymap = keymap;

	glfwPollEvents();
	if(glfwWindowShouldClose(m_window)){
		return true;
	}

	return false;
}

void InputManager::setMouseGrabbed(bool _grabbed){
	if(_grabbed){
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}else{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void InputManager::setVerticalSync(bool _sync){
	glfwSwapInterval(_sync);
}

glm::vec2 InputManager::getWindowSize(){
	int w, h;
	glfwGetWindowSize(m_window, &w, &h);
	return glm::vec2(w, h);
}

glm::vec2 InputManager::getPreviousMousePosition(){
	return m_previousMousePosition;
}

glm::vec2 InputManager::getMousePosition(){
	return mousePosition;
}

glm::vec2 InputManager::getScaledMousePosition(){
	glm::vec2 mousePos = getMousePosition();
	glm::vec2 windowSize = getWindowSize();
	return Utils::mapPoint(glm::vec2(mousePos.x, mousePos.y), glm::vec2(windowSize.x, windowSize.y), glm::vec2(1280.0f, 720.0f));
}

bool InputManager::isKeyDown(int _keyID){
	auto it = keymap.find(_keyID);
	if(it != keymap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::wasKeyDown(int _keyID){
	auto it = m_previousKeymap.find(_keyID);
	if(it != m_previousKeymap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::isKeyPressed(int _keyID){
	return (isKeyDown(_keyID) && !wasKeyDown(_keyID));
}

bool InputManager::isKeyReleased(int _keyID){
	return (!isKeyDown(_keyID) && wasKeyDown(_keyID));
}