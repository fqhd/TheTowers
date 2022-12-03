#include "Clock.hpp"

void Clock::restart(){
	m_time = glfwGetTime();
}

double Clock::getElapsedTime(){
	double duration = glfwGetTime() - m_time;
	return duration;
}
