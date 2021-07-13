#pragma once

#include "GUIRenderer.hpp"
#include "../Input/InputManager.hpp"
#include "../Math/Math.hpp"

class GUIButton {
public:

	GUIButton(const math::vec4& destRect, unsigned int _layer);
	void update(InputManager* _manager, float deltaTime);
	void render(GUIRenderer* renderer);
	bool isPressed();

	unsigned int layer = 0;

private:

	bool m_isPressed = false;
	ColorRGBA8 m_baseColor;
	ColorRGBA8 m_currentColor;
	std::string m_string;

	math::vec4 m_originalRect;
	math::vec4 m_targetRect;
	math::vec4 m_shadowRect;
	math::vec4 m_destRect;

};
