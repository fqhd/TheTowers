#pragma once
#include <string>

#include "Math/Mat4.hpp"
#include "GUIRenderer.hpp"
#include "../Input/InputManager.hpp"

class GUIInput {
public:

	GUIInput(const math::vec4& destRect);
	void update(InputManager* _manager, float deltaTime);
	void render(GUIRenderer* renderer);

private:
	bool m_active;
	std::string input;
};