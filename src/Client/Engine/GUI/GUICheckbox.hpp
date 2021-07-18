#pragma once

#include "GUIRenderer.hpp"
#include "GUIAssets.hpp"
#include "../Utils/Utils.hpp"
#include "../Input/InputManager.hpp"


class GUICheckbox {
public:

	GUICheckbox(const math::vec4& destRect, bool _checked, unsigned int _layer);
	void update(InputManager* _manager, float deltaTime);
	void render(GUIRenderer* _renderer, GUIAssets* _assets);
	bool isChecked();

	unsigned int layer;

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
