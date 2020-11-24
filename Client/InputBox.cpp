#include "InputBox.hpp"
#include <iostream>


void InputBox::init(const sf::FloatRect& box, sf::Font* font){

	m_backgroundRect.setPosition(sf::Vector2f(box.left, box.top));
	m_backgroundRect.setSize(sf::Vector2f(box.width, box.height));

	m_text.setCharacterSize(18);
	m_text.setFillColor(sf::Color::Black);
	m_text.setFont(*font);

	m_text.setPosition(sf::Vector2f(box.left, box.top));

}

void InputBox::update(InputManager& manager, sf::RenderWindow& window){

	if(manager.getLastKeyTyped() != 0){

		std::string string = m_text.getString();

		if(manager.getLastKeyTyped() == 8 && !string.empty()){
			string.pop_back();
		}else{
			if(manager.getLastKeyTyped() != 8)
				string += manager.getLastKeyTyped();
		}

		m_text.setString(string);

	}



}

void InputBox::render(sf::RenderWindow& window){
	window.draw(m_backgroundRect);
	window.draw(m_text);
}

std::string InputBox::getString(){
	return m_text.getString();
}
