#include "InputManager.hpp"
#include "Utils.hpp"


std::unordered_map<unsigned int, bool> InputManager::m_keymap;
std::unordered_map<unsigned int, bool> InputManager::m_previousKeyMap;

std::unordered_map<unsigned int, bool> InputManager::m_mousemap;
std::unordered_map<unsigned int, bool> InputManager::m_previousMouseMap;

glm::vec2 InputManager::m_mousePosition;
glm::vec2 InputManager::m_deltaMousePosition;
float InputManager::m_deltaMouseWheel;
int InputManager::m_lastKeyPressed;


void InputManager::init(GLFWwindow* window){

	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mousePosCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

}

int InputManager::getLastKeyPressed(){
	return m_lastKeyPressed;
}

const glm::vec2& InputManager::getMousePosition(){
	return m_mousePosition;
}

glm::vec2 InputManager::getPercentageMousePosition(){
	return glm::vec2(m_mousePosition.x, m_mousePosition.y);
}

bool InputManager::processInput(GLFWwindow* window){
	if(glfwWindowShouldClose(window)){
		return true;
	}

	for(auto& it : m_keymap){
		m_previousKeyMap[it.first] = it.second;
	}

	for(auto& it : m_mousemap){
		m_previousMouseMap[it.first] = it.second;
	}

	m_deltaMouseWheel = 0;
	m_lastKeyPressed = -1;

	glm::vec2 previousMousePos = m_mousePosition;

	glfwPollEvents();

	m_deltaMousePosition = m_mousePosition - previousMousePos;

	return false;
}



float InputManager::getDeltaMouseWheel() {
	return m_deltaMouseWheel;
}

const glm::vec2& InputManager::getDeltaMousePosition() {
	return m_deltaMousePosition;
}

bool InputManager::isKeyPressed(unsigned int keyID){
	return (isKeyDown(keyID) && !wasKeyDown(keyID));
}

bool InputManager::isKeyReleased(unsigned int keyID){
	return (!isKeyDown(keyID) && wasKeyDown(keyID));
}

bool InputManager::isButtonPressed(unsigned int keyID){
	return (isButtonDown(keyID) && !wasButtonDown(keyID));
}

bool InputManager::isButtonReleased(unsigned int keyID){
	return (!isButtonDown(keyID) && wasButtonDown(keyID));
}

bool InputManager::isButtonDown(unsigned int buttonID){
	auto it = m_mousemap.find(buttonID);
	if(it != m_mousemap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::isKeyDown(unsigned int keyID){
	auto it = m_keymap.find(keyID);
	if(it != m_keymap.end()){
		return it->second;
	}
	return false;
}


bool InputManager::wasKeyDown(unsigned int buttonID){
	auto it = m_previousKeyMap.find(buttonID);
	if(it != m_previousKeyMap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::wasButtonDown(unsigned int buttonID){
	auto it = m_previousMouseMap.find(buttonID);
	if(it != m_previousMouseMap.end()){
		return it->second;
	}
	return false;
}

void InputManager::buttonPressed(unsigned int buttonID){
	m_mousemap[buttonID] = true;
}

void InputManager::buttonReleased(unsigned int buttonID){
	m_mousemap[buttonID] = false;
}

void InputManager::keyPressed(unsigned int keyID){
	m_keymap[keyID] = true;
	m_lastKeyPressed = keyID;
}

void InputManager::keyReleased(unsigned int keyID){
	m_keymap[keyID] = false;
}




//////////////////////////////////////////////////////////////////////////////////
// ********************************** CALLBACKS ********************************//
//////////////////////////////////////////////////////////////////////////////////


void InputManager::keyCallback(GLFWwindow* window, int key, int scanecode, int action, int mods){

	if(action == GLFW_PRESS){
		keyPressed(key);
	} else if (action == GLFW_RELEASE){
		keyReleased(key);
	}

}

void InputManager::mousePosCallback(GLFWwindow* window, double xpos, double ypos){
	m_mousePosition = glm::vec2(xpos, ypos);
}

void InputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
	m_deltaMouseWheel = yoffset;
}

void InputManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){

	if(action == GLFW_PRESS){
		buttonPressed(button);
	}else if(action == GLFW_RELEASE){
		buttonReleased(button);
	}

}
