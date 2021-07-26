#pragma once

// how many frames are used to calculate average frame rate
#define FRAMES_SIZE 50

#include <SFML/System.hpp>
#include "Math.hpp"

class FrameCounter {
public:

	FrameCounter();
	void tick(float delta_time);
	int getAverage() const;

private:

	int m_average = 0;
	void calcAverage();
	float frames[FRAMES_SIZE];
	int current_frame;
	sf::Clock m_updateTimer;
	
};
