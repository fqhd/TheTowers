#include "GUI.hpp"
#include "Window.hpp"

void GUI::updateDestRect(){
	m_destRect = glm::vec4(m_ratio.x * Window::getWidth(), m_ratio.y * Window::getHeight(), m_ratio.z * Window::getWidth(), m_ratio.w * Window::getHeight());
}
