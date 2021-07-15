#pragma once
#include <string>

#include "../Math/Mat4.hpp"
#include "GUIRenderer.hpp"
#include "../Input/InputManager.hpp"
#include <ctime>

class GUIInput {
public:

	GUIInput(const math::vec4& destRect);
	void update(InputManager* _manager);
	void render(GUIRenderer* renderer);

	// int getInt();
	// std::string getString();

private:

	time_t m_last_pressed;
	bool m_active;
	//std::string m_input;

	math::vec4 m_destRect;
	math::vec4 m_outlineRect;

};