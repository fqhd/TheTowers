#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "InputManager.hpp"

class InputBox{
public:


	void init(const sf::FloatRect& box, sf::Font* font);
	void update(InputManager& manager, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);

	std::string getString();

private:

	sf::Text m_text;
	sf::RectangleShape m_backgroundRect;


};