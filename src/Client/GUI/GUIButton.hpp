#pragma once

#include "GUIRenderer.hpp"
#include "GUIAssets.hpp"
#include "InputManager.hpp"
#include <glm/glm.hpp>

class GUIButton {
public:

	void init(const glm::vec4& destRect);
	void update(float deltaTime);
	void render();
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
