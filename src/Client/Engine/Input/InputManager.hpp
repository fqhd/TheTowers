#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>
#include <SFML/Window.hpp>
#include <glm/glm.hpp>


class InputManager {
public:

	void init(sf::Window* _window);
	bool processInput();

	bool isKeyPressed(unsigned int keyID);
	bool isKeyReleased(unsigned int keyID);
	bool isKeyDown(unsigned int keyID);
	bool wasKeyDown(unsigned int keyID);
	bool isButtonPressed(unsigned int keyID);
	bool isButtonReleased(unsigned int keyID);
	bool isButtonDown(unsigned int keyID);
	bool wasButtonDown(unsigned int keyID);
	float getDeltaMouseWheel();
	void centerMouseInWindow();
	glm::vec2 getScaledMousePosition();


private:

	void keyPressed(unsigned int keyID);
	void keyReleased(unsigned int keyID);
	void buttonPressed(unsigned int buttonID);
	void buttonReleased(unsigned int buttonID);
	std::unordered_map<unsigned int, bool> m_keymap;
	std::unordered_map<unsigned int, bool> m_previousKeyMap;
	std::unordered_map<unsigned int, bool> m_mousemap;
	std::unordered_map<unsigned int, bool> m_previousMouseMap;

	static float m_deltaMouseWheel;
	sf::Window* m_window;
	sf::Event m_event;

};
#endif
