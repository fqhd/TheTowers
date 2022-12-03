#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

class Clock {
public:

	void restart();
	double getElapsedTime();

private:

	double m_time = 0.0;

};