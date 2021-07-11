#pragma once

#include "GUIRenderer.hpp"
#include "../Input/InputManager.hpp"

class GUIButton {
public:

	GUIButton(const glm::vec4& destRect, unsigned int _layer);
	void update(InputManager* _manager, float deltaTime);
	void render(GUIRenderer* renderer);
	bool isPressed();

	unsigned int layer = 0;

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
