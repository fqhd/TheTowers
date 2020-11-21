#pragma once
#include "GUIRenderer.hpp"
#include "InputManager.hpp"
#include <SFML/Graphics.hpp>

class GUIButton{
public:

	GUIButton(const glm::vec4& destRect, const ColorRGBA8& color);
	void update(sf::Window& window, InputManager& manager);
	void render(GUIRenderer& renderer);
	bool isPressed();

private:

	bool m_isPressed = false;
	ColorRGBA8 m_baseColor;
	ColorRGBA8 m_currentColor;
	glm::vec4 m_destRect;
	std::string m_string;

};
