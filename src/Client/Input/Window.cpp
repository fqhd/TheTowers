#include "Window.hpp"
#include <iostream>

GLFWwindow* window;

void Window::create(unsigned int _width, unsigned int _height, const char* _title){
	// Initializing GLFW
	if(!glfwInit()){
		std::cout << "Window: Failed to initialize GLFW" << std::endl;
		return;
	}

	// Setting window hints
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Creating the window
	window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
	if(!window){
		std::cout << "Window: Failed to create window" << std::endl;
		return;
	}

	// Create GL context
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Window: Failed to initialize GLAD" << std::endl;
	}

	//Enabling transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enabling depth
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	//Enabling back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Enabling MSAA
	glEnable(GL_MULTISAMPLE);

	// Enabling point size
	glEnable(GL_PROGRAM_POINT_SIZE);

	// Changing the line width(for block outline)
	glLineWidth(1.0f);	
}

GLFWwindow* Window::getWindowPtr(){
	return window;
}

void Window::clear(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
}

void Window::update(){
	glfwSwapBuffers(window);
}

void Window::close(){
	glfwDestroyWindow(window);
	glfwTerminate();
}
