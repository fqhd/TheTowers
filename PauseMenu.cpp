#include "PauseMenu.hpp"
#include "Constants.hpp"
#include <iostream>

void PauseMenu::init(GUIFont* font, Settings& settings){

     m_handler.init(font);

	loadSettingsFromDisk(settings);

     m_handler.images.push_back(Image(glm::vec4(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT), ColorRGBA8(0, 0, 0, 150)));
     m_handler.images.push_back(Image(glm::vec4(SCREEN_WIDTH / 2 - MENU_BG_WIDTH / 2, SCREEN_HEIGHT / 2.0f - MENU_BG_HEIGHT / 2.0f, MENU_BG_WIDTH, MENU_BG_HEIGHT), ColorRGBA8(50, 50, 50, 255)));
     m_handler.images.push_back(Image(glm::vec4(SCREEN_WIDTH / 2 - MENU_WIDTH / 2, SCREEN_HEIGHT / 2.0f - MENU_HEIGHT / 2.0f, MENU_WIDTH, MENU_HEIGHT), ColorRGBA8(20, 20, 20, 255)));
	m_handler.checkboxes.push_back(GUICheckbox(glm::vec4(SCREEN_WIDTH / 2 - MENU_WIDTH / 2 + 50,
		SCREEN_HEIGHT / 2.0f - MENU_HEIGHT / 2.0f + 450, 16, 16), ColorRGBA8(220, 50, 255, 255),
		ColorRGBA8(90, 90, 90, 255), settings.showFPS));
		m_handler.sliders.push_back(GUISlider(glm::vec2(800, 300), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(40, 40, 40, 255)));

}

void PauseMenu::update(sf::Window& window, InputManager& manager, GameStates& state, Settings& settings){
     if(manager.isKeyPressed(sf::Keyboard::Escape)){
          window.setMouseCursorGrabbed(true);
	     window.setMouseCursorVisible(false);
          sf::Mouse::setPosition(sf::Vector2i(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), window);
          state = GameStates::PLAY;

		settings.showFPS = m_handler.checkboxes[0].isChecked();
		writeSettingsToDisk(settings);
     }


     m_handler.update(window, manager);
}

void PauseMenu::render(){
     m_handler.render();
}

void PauseMenu::writeSettingsToDisk(Settings& settings){
	std::ofstream os;
	os.open("res/settings.txt");

	os << "ShowFPS: " << settings.showFPS;

	os.close();
}

void PauseMenu::loadSettingsFromDisk(Settings& settings){
	std::ifstream is;
	is.open("res/settings.txt");
	std::string t;
	while(is >> t){
		if(t == "ShowFPS:"){
			is >> settings.showFPS;
		}
	}
	is.close();
}

void PauseMenu::destroy(){
     m_handler.destroy();
}
