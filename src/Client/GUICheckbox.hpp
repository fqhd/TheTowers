#pragma once

#include "GUIRenderer.hpp"
#include "GUIAssets.hpp"
#include "Utils.hpp"
#include "InputManager.hpp"


class GUICheckbox {
public:

	void init(const math::vec4& destRect, bool _checked = false);
	void update(InputManager* _manager, float deltaTime);
	void render();
	bool isChecked();

private:

	math::vec4 m_originalRect;
	math::vec4 m_targetRect;
	math::vec4 m_shadowRect;
	math::vec4 m_destRect;
	bool m_isChecked = false;

	ColorRGBA8 m_offColor;
	ColorRGBA8 m_onColor;
	ColorRGBA8 m_currentColor;

};
