#pragma once

#include "GUIRenderer.hpp"
#include "GUIAssets.hpp"
#include "Utils.hpp"
#include "InputManager.hpp"


class GUICheckbox {
public:

	void init(const glm::vec4& destRect, bool _checked = false);
	void update(float deltaTime);
	void render();
	bool isChecked();

private:

	glm::vec4 m_originalRect;
	glm::vec4 m_targetRect;
	glm::vec4 m_shadowRect;
	glm::vec4 m_destRect;
	bool m_isChecked = false;

	ColorRGBA8 m_offColor;
	ColorRGBA8 m_onColor;
	ColorRGBA8 m_currentColor;

};
