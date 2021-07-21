#pragma once
#include <SFML/Window.hpp>
#include <unordered_map>
#include <vector>
#include "../Math/Math.hpp"


class InputManager {
public:

	void init(sf::Window* _window);
	bool processInput();

	bool isKeyPressed(int _keyID);
	bool isKeyReleased(int _keyID);
	bool isKeyDown(int _keyID);
	bool wasKeyDown(int _keyID);

	bool isButtonPressed(int _buttonID);
	bool isButtonReleased(int _buttonID);
	bool isButtonDown(int _buttonID);
	bool wasButtonDown(int _buttonID);
	bool hasFocus();

	void setVerticalSync(bool _sync);
	void setMouseVisible(bool _visible);
	void centerMouse();
	math::uvec2 getWindowSize();
	math::ivec2 getMousePosition();
	math::ivec2 getPreviousMousePosition();

private:

	// Private functions
	void keyPressed(unsigned int _keyID);
	void keyReleased(unsigned int _keyID);
	void buttonPressed(unsigned int _buttonID);
	void buttonReleased(unsigned int _buttonID);

	std::unordered_map<unsigned int, bool> m_keymap;
	std::unordered_map<unsigned int, bool> m_previousKeymap;
	std::unordered_map<unsigned int, bool> m_buttonmap;
	std::unordered_map<unsigned int, bool> m_previousButtonmap;
	math::uvec2 m_windowSize;
	math::ivec2 m_mousePosition;
	math::ivec2 m_previousMousePosition;
	sf::Window* m_window;
	sf::Event m_event;
	bool m_hasFocus = true;



};

