#pragma once
#include <string>
#include <numeric>
#include "../Math/Math.hpp"
#include "GUIRenderer.hpp"
#include "../Input/InputManager.hpp"
#include "../Utils/Utils.hpp"


class GUIInput {
public:
	void init(const math::vec4& destRect);
	void update(InputManager* _manager);
	void render(GUIRenderer* _renderer);
private:
	math::vec4 m_destRect;
	math::vec4 m_outlineRect;
	std::string m_input;
	bool m_onFocus;
};