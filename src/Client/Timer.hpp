#pragma once

#include <chrono>

class Timer {
public:

	void restart();
	double getElapsedTime();

private:

	std::chrono::_V2::system_clock::time_point m_time;

};