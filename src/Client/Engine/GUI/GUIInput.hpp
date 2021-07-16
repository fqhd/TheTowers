#pragma once
#include <string>
#include <vector>
#include <numeric>
#include "../Math/Mat4.hpp"
#include "GUIRenderer.hpp"
#include "../Input/InputManager.hpp"
#include "GUILabel.hpp"

class GUIInput {
public:

	GUIInput(const math::vec4& destRect);
	void update(InputManager* _manager);
	void render(GUIRenderer* renderer);


private:

	bool m_focused;
	GUILabel m_label;
	std::string m_input;
	std::vector<int> supported_keys;
	math::vec4 m_destRect;
	math::vec4 m_outlineRect;

};