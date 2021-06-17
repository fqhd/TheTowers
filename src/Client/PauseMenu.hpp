#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "GameStates.hpp"
#include "Engine/GUI/GUIHandler.hpp"
#include "Player.hpp"
#include <fstream>


class PauseMenu {
public:

	void init(InputManager* _manager, sf::Window* _window, GUIFont* font);
	void update(GameStates& _state);
	void render();
	void destroy();

private:

	GUIHandler m_handler;
	InputManager* m_manager;
	sf::Window* m_window;

	void addImages();
	void addCheckboxes();
	void addText();
	void addButtons();


};

#endif
