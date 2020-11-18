#include "Button.hpp"


void Button::init(const sf::FloatRect& destRect, const char* text, sf::Font* font){

	m_rect.setPosition(sf::Vector2f(destRect.left, destRect.top));
	m_rect.setSize(sf::Vector2f(destRect.width, destRect.height));

	m_text.setFillColor(sf::Color::White);
	m_text.setString(text);
	m_text.setCharacterSize(18);
	m_text.setFont(*font);

	m_text.setPosition(sf::Vector2f((destRect.left + destRect.width/2) - m_text.getGlobalBounds().width/2, destRect.top));

}

void Button::update(InputManager& manager, sf::RenderWindow& window){

	m_isPressed = false;
	m_rect.setFillColor(sf::Color(120, 130, 200));

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	if(m_rect.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))){
		m_rect.setFillColor(sf::Color(80, 100, 170));
		if(manager.isKeyDown(sf::Mouse::Left)){
			m_rect.setFillColor(sf::Color(50, 70, 150));
		}else if(manager.isKeyReleased(sf::Mouse::Left)) {
			m_isPressed = true;
		}
	}

}

void Button::render(sf::RenderWindow& window){
	window.draw(m_rect);
	window.draw(m_text);
}

bool Button::isPressed(){
	return m_isPressed;
}