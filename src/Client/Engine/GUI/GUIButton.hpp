#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include "GUIRenderer.hpp"
#include "../Input/InputManager.hpp"

class GUIButton {
public:

	GUIButton(const glm::vec4& destRect);
	void update(InputManager* _manager, float deltaTime);
	void render(GUIRenderer& renderer);
	bool isPressed();

private:

	bool m_isPressed = false;
	ColorRGBA8 m_baseColor;
	ColorRGBA8 m_currentColor;
	std::string m_string;

	glm::vec4 m_originalRect;
	glm::vec4 m_targetRect;
	glm::vec4 m_shadowRect;
	glm::vec4 m_destRect;

};

#endif
