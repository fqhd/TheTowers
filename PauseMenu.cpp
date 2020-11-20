#include "PauseMenu.hpp"
#include "Constants.hpp"

void PauseMenu::init(sf::Window& window, GUIFont* font, Settings& settings){

     m_handler.init(font);

     loadSettingsFromDisk(settings);
     if(settings.vsync)
          window.setVerticalSyncEnabled(true);
     else
          window.setVerticalSyncEnabled(false);

     m_handler.images.push_back(Image(glm::vec4(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT), ColorRGBA8(0, 0, 0, 150)));
     m_handler.images.push_back(Image(glm::vec4(SCREEN_WIDTH / 2 - MENU_BG_WIDTH / 2, SCREEN_HEIGHT / 2.0f - MENU_BG_HEIGHT / 2.0f, MENU_BG_WIDTH, MENU_BG_HEIGHT), ColorRGBA8(50, 50, 50, 255)));
     m_handler.images.push_back(Image(glm::vec4(SCREEN_WIDTH / 2 - MENU_WIDTH / 2, SCREEN_HEIGHT / 2.0f - MENU_HEIGHT / 2.0f, MENU_WIDTH, MENU_HEIGHT), ColorRGBA8(20, 20, 20, 255)));
     m_handler.images.push_back(Image(glm::vec4(600, 190, 128, 128), ColorRGBA8(0, 0, 0, 255)));

     m_handler.checkboxes.push_back(GUICheckbox(glm::vec4(SCREEN_WIDTH / 2 - MENU_WIDTH / 2 + 50,
          SCREEN_HEIGHT / 2.0f - MENU_HEIGHT / 2.0f + 450, 16, 16), ColorRGBA8(220, 50, 255, 255),
          ColorRGBA8(90, 90, 90, 255), settings.showFPS));


     m_handler.checkboxes.push_back(GUICheckbox(glm::vec4(SCREEN_WIDTH / 2 - MENU_WIDTH / 2 + 50,
          SCREEN_HEIGHT / 2.0f - MENU_HEIGHT / 2.0f + 400, 16, 16), ColorRGBA8(220, 50, 255, 255),
          ColorRGBA8(90, 90, 90, 255), settings.vsync));

     m_handler.sliders.push_back(GUISlider(glm::vec2(800, 300), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), settings.maxFps/1000.0f));

     m_handler.sliders.push_back(GUISlider(glm::vec2(300, 200), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), 0.0f));
     m_handler.sliders.push_back(GUISlider(glm::vec2(300, 250), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), 0.0f));
     m_handler.sliders.push_back(GUISlider(glm::vec2(300, 300), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), 0.0f));


}

void PauseMenu::update(sf::Window& window, InputManager& manager, GameStates& state, Settings& settings, uint8_t& blockID){
     if(manager.isKeyPressed(sf::Keyboard::Escape)){
          window.setMouseCursorGrabbed(true);
	     window.setMouseCursorVisible(false);
          sf::Mouse::setPosition(sf::Vector2i(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), window);
          state = GameStates::PLAY;

          settings.showFPS = m_handler.checkboxes[0].isChecked();
          settings.vsync = m_handler.checkboxes[1].isChecked();
          if(settings.vsync)
               window.setVerticalSyncEnabled(true);
          else
               window.setVerticalSyncEnabled(false);
          settings.maxFps = (int)(m_handler.sliders[0].getValue() * 1000.0f) <= 0 ? 1 : (int)(m_handler.sliders[0].getValue() * 1000.0f);

          unsigned int blueValue = ((int)(m_handler.sliders[3].getValue() * 5)) * 36;
          unsigned int greenValue = ((int)(m_handler.sliders[2].getValue() * 5)) * 6;
          unsigned int redValue = (int)(m_handler.sliders[1].getValue() * 5);

          blockID = blueValue + greenValue + redValue;
		writeSettingsToDisk(settings);
     }

     m_handler.images[3].color = ColorRGBA8(m_handler.sliders[1].getValue() * 255, m_handler.sliders[2].getValue() * 255, m_handler.sliders[3].getValue() * 255, 255);

     m_handler.update(window, manager);

}

void PauseMenu::render(){

     m_handler.render();

     m_handler.renderFont(std::to_string((int)(m_handler.sliders[0].getValue() * 1000.0f) <= 0 ? 1 : (int)(m_handler.sliders[0].getValue() * 1000.0f)), 920, 316, 0.5f, ColorRGBA8(255, 255, 255, 255));

     m_handler.renderFont("R: " + std::to_string((int)(m_handler.sliders[1].getValue() * 216)), 220, 200, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("G: " + std::to_string((int)(m_handler.sliders[2].getValue() * 216)), 220, 250, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("B: " + std::to_string((int)(m_handler.sliders[3].getValue() * 216)), 220, 300, 0.5f, ColorRGBA8(255, 255, 255, 255));

}

void PauseMenu::writeSettingsToDisk(Settings& settings){
	std::ofstream os;
	os.open("res/settings.txt");

     os << "ShowFPS: " << settings.showFPS << std::endl;
     os << "vsync: " << settings.vsync << std::endl;
     os << "maxFps: " << settings.maxFps << std::endl;

	os.close();
}

void PauseMenu::loadSettingsFromDisk(Settings& settings){
	std::ifstream is;
	is.open("res/settings.txt");
	std::string t;
	while(is >> t){
          if(t == "ShowFPS:"){
               is >> settings.showFPS;
          }else if(t == "maxFps:"){
               is >> settings.maxFps;
          }else if(t == "vsync:"){
               is >> settings.vsync;
          }

	}
	is.close();
}

void PauseMenu::destroy(){
     m_handler.destroy();
}
