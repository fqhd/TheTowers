#include <SFML/Graphics.hpp>
#include "InputManager.hpp"


class Button {
public:

	void init(const sf::FloatRect& destRect, const char* text, sf::Font* font);
	void update(InputManager& manager, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);

	bool isPressed();

private:

	bool m_isPressed = false;
	sf::RectangleShape m_rect;
	sf::Text m_text;

};
