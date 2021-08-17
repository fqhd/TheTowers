#pragma once
#include <string>
#include <numeric>
#include "Math.hpp"
#include "GUIRenderer.hpp"
#include "InputManager.hpp"
#include "Utils.hpp"
#include "ColorRGBA8.hpp"

class GUIInput {
public:
	void init(const math::vec4& destRect, 
	          const ColorRGBA8& backgroundColor=ColorRGBA8(150, 150, 150, 255), 
	          const ColorRGBA8& outlineColor=ColorRGBA8(200, 200, 200, 255), 
			  const ColorRGBA8& activeOutlineColor=ColorRGBA8());
	void update(InputManager* _manager);
	void render(GUIRenderer* _renderer);
	bool wasSubmitted();
private:
	math::vec4 m_destRect;
	math::vec4 m_outlineRect;
	std::string m_input;
	ColorRGBA8 m_backgroundColor;
	ColorRGBA8 m_outlineColor;
	ColorRGBA8 m_activeOutlineColor;
	bool m_onFocus;
	bool m_wasSubmitted;
};