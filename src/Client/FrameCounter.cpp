#include "FrameCounter.hpp"


FrameCounter::FrameCounter() {
	current_frame = 0;
}


void FrameCounter::tick(float delta_time) {
	frames[current_frame] = 1.0f / delta_time;
	current_frame = current_frame < FRAMES_SIZE ? current_frame + 1 : 0;
}

float FrameCounter::get_average() {
	float sum = 0.0f;
	for (int i = 0; i < current_frame; i++) {
		sum += frames[i];
		
	}
	return sum/current_frame;
}

int FrameCounter::get_current_frame() {
	return current_frame;
}
