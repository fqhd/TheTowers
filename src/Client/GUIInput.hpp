#pragma once
#include <string>
#include <numeric>
#include "Math.hpp"
#include "GUIRenderer.hpp"
#include "InputManager.hpp"
#include "Utils.hpp"


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