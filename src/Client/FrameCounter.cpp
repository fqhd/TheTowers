#include "FrameCounter.hpp"


FrameCounter::FrameCounter() {
	current_frame = 0;
}


void FrameCounter::tick(float delta_time) {
	frames[current_frame] = 1.0f / delta_time;
	current_frame = current_frame < FRAMES_SIZE ? current_frame + 1 : 0;

	if(m_updateTimer.getElapsedTime().asSeconds() >= 1.0f){
		calcAverage();
		m_updateTimer.restart();
	}
}

void FrameCounter::calcAverage() {
	float sum = 0.0f;
	for (int i = 0; i < current_frame; i++) {
		sum += frames[i];
	}
	m_average = sum/current_frame;
}

int FrameCounter::getAverage() const {
	return m_average;
}