#pragma once

class FrameCounter {
public:

	void tick(float delta_time);
	int getFrameRate() const;

private:

	int m_fps = 0;
	int m_currentFPS = 0;;
	float m_elapsedTime = 0.0f;
	
};
