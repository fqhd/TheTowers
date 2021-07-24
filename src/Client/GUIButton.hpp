#pragma once

#include "GUIRenderer.hpp"
#include "GUIAssets.hpp"
#include "InputManager.hpp"
#include "Math.hpp"

class GUIButton {
public:

	void init(const math::vec4& destRect);
	void update(InputManager* _manager, float deltaTime);
	void render(GUIRenderer* _renderer);
	bool isPressed();

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
