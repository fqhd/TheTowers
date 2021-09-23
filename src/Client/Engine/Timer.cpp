#include "Timer.hpp"

void Timer::restart(){
	m_time = glfwGetTime();
}

double Timer::getElapsedTime(){
	double duration = glfwGetTime() - m_time;
	return duration;
}
