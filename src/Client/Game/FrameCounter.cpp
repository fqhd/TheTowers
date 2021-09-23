#include "FrameCounter.hpp"


void FrameCounter::tick(float delta_time) {
	m_fps++;
	m_elapsedTime += delta_time;
	if(m_elapsedTime > 1.0f){
		m_elapsedTime = 0.0f;
		m_currentFPS = m_fps;
		m_fps = 0;
	}
}

int FrameCounter::getFrameRate() const {
	return m_currentFPS;
}