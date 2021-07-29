#include "Timer.hpp"

void Timer::restart(){
	m_time = std::chrono::high_resolution_clock::now();
}

double Timer::getElapsedTime(){
	std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - m_time;
	return duration.count();
}
