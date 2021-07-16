#pragma once
#include <string>
#include <vector>
#include <numeric>
#include "../Math/Mat4.hpp"
#include "../Input/InputManager.hpp"
#include "GUILabel.hpp"
#include "GUIRenderer.hpp"
#include "GUIFont.hpp"
#include "GUIFontShader.hpp"

class GUIInput {
public:

	GUIInput(const math::vec4& destRect);
	void update(InputManager* _manager);
	void render(GUIRenderer* renderer);


private:

	bool m_focused;
	GUIFontShader m_fontShader;
	GUIFont m_font;
	GUILabel m_label;
	std::string m_input;
	std::vector<int> supported_keys;
	math::vec4 m_destRect;
	math::vec4 m_outlineRect;

};