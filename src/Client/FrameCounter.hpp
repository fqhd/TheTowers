#pragma once

// of many frames are used to calculate average
#define FRAMES_SIZE 10
#define UNDEFINED_FRAME -1.0f
class FrameCounter
{
public:

	FrameCounter();
	void tick(float delta_time);
	float get_average();

private:

	float frames[FRAMES_SIZE];
	int current_frame;
};