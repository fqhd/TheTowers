#include "FrameCounter.hpp"


FrameCounter::FrameCounter() {
	for (int i = 0; i < FRAMES_SIZE; i++) {
		frames[i] = UNDEFINED_FRAME;
	}
	current_frame = 0;
} 


void FrameCounter::tick(float delta_time) {
	frames[current_frame] = 1/delta_time;
	current_frame = current_frame < FRAMES_SIZE ? current_frame+1 : 0;
}

float FrameCounter::get_average() {
	int defined = 0;
	float sum = 0.0f;
	for (int i = 0; i < FRAMES_SIZE; i++) {
		if (frames[i] != UNDEFINED_FRAME) {
			defined++;
			sum += frames[i];
		}
	}
	return sum/defined;
}