#include "InputManager.hpp"
#include "../Utils/Utils.hpp"
#include <iostream>


void InputManager::init(GLFWwindow* _window) {
	m_window = _window;
}

bool InputManager::processInput() {
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

glm::vec2 InputManager::getSize(){
	int w, h;
	glfwGetWindowSize(m_window, &w, &h);
	return glm::vec2(w, h);
}

glm::vec2 InputManager::getMousePosition(){
	double x, y;
	glfwGetCursorPos(m_window, &x, &y);
	return glm::vec2(x, y);
}

glm::vec2 InputManager::getScaledMousePosition(){
	glm::vec2 mousePos = getMousePosition();
	glm::vec2 windowSize = getSize();
	return Utils::mapPoint(glm::vec2(mousePos.x, mousePos.y), glm::vec2(windowSize.x, windowSize.y), glm::vec2(1280.0f, 720.0f));
}


bool InputManager::isKeyPressed(unsigned int _keyID){
	if(glfwGetKey(m_window, _keyID) == GLFW_PRESS){
		return true;
	}
	return false;
}
bool InputManager::isKeyReleased(unsigned int _keyID){
	if(glfwGetKey(m_window, _keyID) == GLFW_RELEASE){
		return true;
	}
	return false;
}