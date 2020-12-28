#include "PauseMenu.hpp"
#include "Constants.hpp"
#include <iostream>

void PauseMenu::init(GUIFont* font, Settings& settings){

     m_handler.init(font);

     loadSettingsFromDisk(settings);
     if(settings.vsync)
          Window::setVerticalSyncEnabled(true);
     else
          Window::setVerticalSyncEnabled(false);

     m_handler.images.push_back(GUIImage(glm::vec4(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT), ColorRGBA8(0, 0, 0, 150)));
     m_handler.images.push_back(GUIImage(glm::vec4(SCREEN_WIDTH / 2 - MENU_BG_WIDTH / 2, SCREEN_HEIGHT / 2.0f - MENU_BG_HEIGHT / 2.0f, MENU_BG_WIDTH, MENU_BG_HEIGHT), ColorRGBA8(50, 50, 50, 255)));
     m_handler.images.push_back(GUIImage(glm::vec4(SCREEN_WIDTH / 2 - MENU_WIDTH / 2, SCREEN_HEIGHT / 2.0f - MENU_HEIGHT / 2.0f, MENU_WIDTH, MENU_HEIGHT), ColorRGBA8(20, 20, 20, 255)));
     m_handler.images.push_back(GUIImage(glm::vec4(600, 190, 128, 128), ColorRGBA8(0, 0, 0, 255)));

     m_handler.checkboxes.push_back(GUICheckbox(glm::vec4(SCREEN_WIDTH / 2 - MENU_WIDTH / 2 + 50,
          SCREEN_HEIGHT / 2.0f - MENU_HEIGHT / 2.0f + 450, 16, 16), ColorRGBA8(220, 50, 255, 255),
          ColorRGBA8(90, 90, 90, 255), settings.showFPS));


     m_handler.checkboxes.push_back(GUICheckbox(glm::vec4(SCREEN_WIDTH / 2 - MENU_WIDTH / 2 + 50,
          SCREEN_HEIGHT / 2.0f - MENU_HEIGHT / 2.0f + 400, 16, 16), ColorRGBA8(220, 50, 255, 255),
          ColorRGBA8(90, 90, 90, 255), settings.vsync));

     m_handler.sliders.push_back(GUISlider(glm::vec2(800, 300), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), settings.maxFps));

     m_handler.sliders.push_back(GUISlider(glm::vec2(300, 200), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), 1.0f));
     m_handler.sliders.push_back(GUISlider(glm::vec2(300, 250), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), 1.0f));
     m_handler.sliders.push_back(GUISlider(glm::vec2(300, 300), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), 1.0f));
     m_handler.sliders.push_back(GUISlider(glm::vec2(500, 150), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), settings.mouseSensibility));
     m_handler.sliders.push_back(GUISlider(glm::vec2(500, 100), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), settings.playerSpeed));
     m_handler.sliders.push_back(GUISlider(glm::vec2(800, 150), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), settings.range));


     m_handler.boxes.push_back(GUISelectbox(glm::vec4(850, 425, 200, 30), ColorRGBA8(255, 255, 255, 255), 3));

     m_handler.keyboxes.push_back(GUIKeybox(glm::vec4(220 + 100, 620, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.front));
     m_handler.keyboxes.push_back(GUIKeybox(glm::vec4(220 + 100, 580, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.back));
     m_handler.keyboxes.push_back(GUIKeybox(glm::vec4(420 + 100, 620, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.left));
     m_handler.keyboxes.push_back(GUIKeybox(glm::vec4(420 + 100, 580, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.right));
     m_handler.keyboxes.push_back(GUIKeybox(glm::vec4(620 + 100, 620, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.up));
     m_handler.keyboxes.push_back(GUIKeybox(glm::vec4(620 + 100, 580, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.down));


}

void PauseMenu::update(GameStates& state, Settings& settings, Player& player){
     if(InputManager::isKeyPressed(GLFW_KEY_ESCAPE)){
          Window::setMouseCursorGrabbed(true);
          state = GameStates::PLAY;

          settings.showFPS = m_handler.checkboxes[0].isChecked();
          settings.vsync = m_handler.checkboxes[1].isChecked();
          if(settings.vsync)
               Window::setVerticalSyncEnabled(true);
          else
               Window::setVerticalSyncEnabled(false);
          settings.maxFps = m_handler.sliders[0].getValue();

          unsigned int blueValue = ((int)(m_handler.sliders[3].getValue() * 5)) * 36;
          unsigned int greenValue = ((int)(m_handler.sliders[2].getValue() * 5)) * 6;
          unsigned int redValue = (int)(m_handler.sliders[1].getValue() * 5);

          player.selectedBlock = blueValue + greenValue + redValue;

          settings.mouseSensibility = m_handler.sliders[4].getValue();
          settings.playerSpeed = m_handler.sliders[5].getValue();

          settings.front = m_handler.keyboxes[0].getValue();
          settings.back = m_handler.keyboxes[1].getValue();
          settings.left = m_handler.keyboxes[2].getValue();
          settings.right = m_handler.keyboxes[3].getValue();
          settings.up = m_handler.keyboxes[4].getValue();
          settings.down = m_handler.keyboxes[5].getValue();
          settings.range = m_handler.sliders[6].getValue();

		writeSettingsToDisk(settings);
     }

     m_handler.images[3].color = ColorRGBA8(m_handler.sliders[1].getValue() * 255, m_handler.sliders[2].getValue() * 255, m_handler.sliders[3].getValue() * 255, 255);

     m_handler.update();

}

void PauseMenu::render(){

     m_handler.render();

     m_handler.renderFont("Show FPS", 280, 510, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("Vertical Sync", 280, 460, 0.5f, ColorRGBA8(255, 255, 255, 255));

     m_handler.renderFont(std::to_string((int)(m_handler.sliders[0].getValue() * MAX_FPS)), 920, 316, 0.5f, ColorRGBA8(255, 255, 255, 255));

     m_handler.renderFont("R: " + std::to_string((int)(m_handler.sliders[1].getValue() * 255)), 220, 200, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("G: " + std::to_string((int)(m_handler.sliders[2].getValue() * 255)), 220, 250, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("B: " + std::to_string((int)(m_handler.sliders[3].getValue() * 255)), 220, 300, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("Mouse Sensibility: " + std::to_string((int)(m_handler.sliders[4].getValue() * MAX_SENSIBILITY)), 220, 150, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("Player Speed: " + std::to_string((int)(m_handler.sliders[5].getValue() * MAX_SPEED)), 220, 100, 0.5f, ColorRGBA8(255, 255, 255, 255));

     m_handler.renderFont("Fullscreen", 870, 430, 0.5f, ColorRGBA8(0, 0, 0, 255));
     m_handler.renderFont("Borderless", 870, 460, 0.5f, ColorRGBA8(0, 0, 0, 255));
     m_handler.renderFont("Windowed", 870, 490, 0.5f, ColorRGBA8(0, 0, 0, 255));
     m_handler.renderFont("RenderDistance", 850, 110, 0.5f, ColorRGBA8(255, 255, 255, 255));

     m_handler.renderFont("Front: ", 220, 620, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("Back: ", 220, 580, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("Left: ", 420, 620, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("Right: ", 420, 580, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("Up: ", 620, 620, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("Down: ", 620, 580, 0.5f, ColorRGBA8(255, 255, 255, 255));

}

void PauseMenu::writeSettingsToDisk(Settings& settings){
	std::ofstream os;
	os.open("res/settings.txt");

     os << "ShowFPS: " << settings.showFPS << std::endl;
     os << "vsync: " << settings.vsync << std::endl;
     os << "maxFps: " << settings.maxFps << std::endl;
     os << "PlayerSpeed: " << settings.playerSpeed << std::endl;
     os << "MouseSensibility: " << settings.mouseSensibility << std::endl;
     os << "Front: " << settings.front << std::endl;
     os << "Back: " << settings.back << std::endl;
     os << "Up: " << settings.up << std::endl;
     os << "Down: " << settings.down << std::endl;
     os << "Left: " << settings.left << std::endl;
     os << "Right: " << settings.right << std::endl;
     os << "RenderDistance: " << settings.range << std::endl;

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
          }else if(t == "PlayerSpeed:"){
               is >> settings.playerSpeed;
          }else if(t == "MouseSensibility:"){
               is >> settings.mouseSensibility;
          }else if(t == "Front:"){
               is >> settings.front;
          }else if(t == "Back:"){
               is >> settings.back;
          }else if(t == "Up:"){
               is >> settings.up;
          }else if(t == "Down:"){
               is >> settings.down;
          }else if(t == "Left:"){
               is >> settings.left;
          }else if(t == "Right:"){
               is >> settings.right;
          }else if(t == "RenderDistance:"){
               is >> settings.range;
          }

	}
	is.close();
}

void PauseMenu::destroy(){
     m_handler.destroy();
}
