#include "InputManager.hpp"
#include "../Utils/Utils.hpp"
#include <iostream>


void InputManager::init(GLFWwindow* _window) {
	m_window = _window;
}

bool InputManager::processInput() {
	m_previousMousePosition = m_mousePosition;

	glfwPollEvents();
	if(glfwWindowShouldClose(m_window)){
		return true;
	}

	// Updating variables
	updateMousePos();

	return false;
}

void InputManager::updateMousePos(){
	double x, y;
	glfwGetCursorPos(m_window, &x, &y);
	m_mousePosition = glm::vec2(x, y);
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
	return m_mousePosition;
}

glm::vec2 InputManager::getScaledMousePosition(){
	glm::vec2 mousePos = getMousePosition();
	glm::vec2 windowSize = getWindowSize();
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