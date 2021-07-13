#include "DebugMenu.hpp"
#include "FrameCounter.hpp"

void DebugMenu::init(Game* _game, GUICanvas* _canvas){
	m_game = _game;
	m_canvas = _canvas;
	initGUI();
}

void DebugMenu::render(){
	updateGUI();
	m_canvas->render();
}

void DebugMenu::initGUI(){
	m_canvas->labels.push_back(GUILabel(std::string("FPS: "), glm::vec2(25, 675), ColorRGBA8()));
	m_canvas->labels.push_back(GUILabel(std::string("X: "), glm::vec2(25, 625), ColorRGBA8()));
	m_canvas->labels.push_back(GUILabel(std::string("Y: "), glm::vec2(25, 575), ColorRGBA8()));
	m_canvas->labels.push_back(GUILabel(std::string("Z: "), glm::vec2(25, 525), ColorRGBA8()));
}

void DebugMenu::updateGUI(){
	glm::vec3 camPos = m_game->camera.getPosition();
	
	if (m_game->m_framecounter.get_current_frame() == FRAMES_SIZE-1) {
		m_canvas->labels[0].setString("FPS: " + std::to_string((int)m_game->m_framecounter.get_average()));
	}
	m_canvas->labels[1].setString("X: " + std::to_string(camPos.x));
	m_canvas->labels[2].setString("Y: " + std::to_string(camPos.y));
	m_canvas->labels[3].setString("Z: " + std::to_string(camPos.z));
}