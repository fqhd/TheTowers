#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

class InputManager{
public:

	void processInput(sf::Window& window);

	bool isKeyPressed(unsigned int keyID);
	bool isKeyReleased(unsigned int keyID);
	bool isKeyDown(unsigned int keyID);
	bool wasKeyDown(unsigned int keyID);

	const glm::vec2& getMousePosition();

	bool isCloseRequested();

	char getLastKeyPressed();



private:

	void keyPressed(unsigned int keyID);
	void keyReleased(unsigned int keyID);

	sf::Event m_event;
	std::unordered_map<unsigned int, bool> m_keymap;
	std::unordered_map<unsigned int, bool> m_previousKeyMap;

	glm::vec2 m_mousePosition;
	bool m_isCloseRequested = false;
	char m_character;

};
