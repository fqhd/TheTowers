#include "PauseMenu.hpp"
#include "Constants.hpp"
#include <iostream>

void PauseMenu::init(GUIFont* font){

     m_handler.init(font);

     m_handler.buttons.push_back(GUIButton(glm::vec4(SCREEN_WIDTH / 2 - 100, 200, 200, 20), ColorRGBA8(75, 100, 255, 255)));
     m_handler.images.push_back(Image(glm::vec4(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT), ColorRGBA8(0, 0, 0, 150)));
     m_handler.images.push_back(Image(glm::vec4(SCREEN_WIDTH / 2 - MENU_BG_WIDTH / 2, SCREEN_HEIGHT / 2.0f - MENU_BG_HEIGHT / 2.0f, MENU_BG_WIDTH, MENU_BG_HEIGHT), ColorRGBA8(50, 50, 50, 255)));
     m_handler.images.push_back(Image(glm::vec4(SCREEN_WIDTH / 2 - MENU_WIDTH / 2, SCREEN_HEIGHT / 2.0f - MENU_HEIGHT / 2.0f, MENU_WIDTH, MENU_HEIGHT), ColorRGBA8(20, 20, 20, 255)));
     m_handler.checkboxes.push_back(GUICheckbox(glm::vec4(SCREEN_WIDTH / 2 - MENU_WIDTH / 2 + 50, SCREEN_HEIGHT / 2.0f - MENU_HEIGHT / 2.0f + 300, 16, 16), ColorRGBA8(220, 50, 255, 255), ColorRGBA8(90, 90, 90, 255)));
     m_handler.checkboxes.push_back(GUICheckbox(glm::vec4(SCREEN_WIDTH / 2 - MENU_WIDTH / 2 + 50, SCREEN_HEIGHT / 2.0f - MENU_HEIGHT / 2.0f + 350, 16, 16), ColorRGBA8(220, 50, 255, 255), ColorRGBA8(90, 90, 90, 255)));
     m_handler.checkboxes.push_back(GUICheckbox(glm::vec4(SCREEN_WIDTH / 2 - MENU_WIDTH / 2 + 50, SCREEN_HEIGHT / 2.0f - MENU_HEIGHT / 2.0f + 400, 16, 16), ColorRGBA8(220, 50, 255, 255), ColorRGBA8(90, 90, 90, 255)));
     m_handler.checkboxes.push_back(GUICheckbox(glm::vec4(SCREEN_WIDTH / 2 - MENU_WIDTH / 2 + 50, SCREEN_HEIGHT / 2.0f - MENU_HEIGHT / 2.0f + 450, 16, 16), ColorRGBA8(220, 50, 255, 255), ColorRGBA8(90, 90, 90, 255)));
     m_handler.sliders.push_back(GUISlider(glm::vec2(800, 300), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(40, 40, 40, 255)));
     m_handler.sliders.push_back(GUISlider(glm::vec2(800, 350), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(40, 40, 40, 255)));
     m_handler.sliders.push_back(GUISlider(glm::vec2(800, 400), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(40, 40, 40, 255)));

}

void PauseMenu::update(sf::Window& window, InputManager& manager, GameStates& state){
     if(manager.isKeyPressed(sf::Keyboard::Escape)){
          window.setMouseCursorGrabbed(true);
	     window.setMouseCursorVisible(false);
          sf::Mouse::setPosition(sf::Vector2i(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), window);
          state = GameStates::PLAY;
     }
     m_handler.update(window, manager);
}

void PauseMenu::render(){
     m_handler.render();

     m_handler.renderFont("example font", 230, 300, 1.0f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("example font", 230, 300, 1.0f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("example font", 230, 300, 1.0f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("example font", 230, 300, 1.0f, ColorRGBA8(255, 255, 255, 255));

     m_handler.renderFont("MENU", SCREEN_WIDTH / 2 - 65, 500, 1.0f, ColorRGBA8(255, 255, 255, 255));

}

void PauseMenu::destroy(){
     m_handler.destroy();
}
