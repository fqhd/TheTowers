#pragma once

// how many frames are used to calculate average frame rate
#define FRAMES_SIZE 50

class FrameCounter {
public:

	FrameCounter();
	void tick(float delta_time);
	float get_average();
	int get_current_frame();

private:
	float frames[FRAMES_SIZE];
	int current_frame;
	
};
